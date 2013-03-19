/*-----------------------------------------------------------------------------
 This source file is part of Hopsan NG

 Copyright (c) 2011
    Mikael Axin, Robert Braun, Alessandro Dell'Amico, Björn Eriksson,
    Peter Nordin, Karl Pettersson, Petter Krus, Ingo Staack

 This file is provided "as is", with no guarantee or warranty for the
 functionality or reliability of the contents. All contents in this file is
 the original work of the copyright holders at the Division of Fluid and
 Mechatronic Systems (Flumes) at Linköping University. Modifying, using or
 redistributing any part of this file is prohibited without explicit
 permission from the copyright holders.
-----------------------------------------------------------------------------*/

//!
//! @file   HydraulicPressureReliefValve.hpp
//! @author Robert Braun <robert.braun@liu.se>
//! @date   2010-01-22
//!
//! @brief Contains a hydraulic pressure relief valve with first order dynamics and signal and input signal
//! Written by Petter Krus 901015
//! Revised by Petter Krus 920324
//! Translated to HOPSAN NG by Robert Braun 100122
//! Modified to contain input signal by Andreas Klintemyr 111101
//$Id$

#ifndef HYDRAULICPRESSURERELIEFVALVE_HPP_INCLUDED
#define HYDRAULICPRESSURERELIEFVALVE_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"

namespace hopsan {

    //!
    //! @brief A Hydraulic Pressure Releife Valve
    //! @ingroup HydraulicComponents
    //!
    class HydraulicPressureReliefValve : public ComponentQ
    {
    private:
        double x0, pmax, tao, Kcs, Kcf, Cs, Cf, qnom, pnom, ph, x0max;
        double mPrevX0;

        double *mpND_in, *mpND_out, *mpND_p1, *mpND_q1, *mpND_c1, *mpND_Zc1, *mpND_p2, *mpND_q2, *mpND_c2, *mpND_Zc2;

        TurbulentFlowFunction mTurb;
        ValveHysteresis mHyst;
        FirstOrderTransferFunction mFilterLP;
        Port *mpP1, *mpP2, *mpIn, *mpOut;

    public:
        static Component *Creator()
        {
            return new HydraulicPressureReliefValve();
        }

        void configure()
        {
            pmax = 20000000;
            tao = 0.01;
            Kcs = 0.00000001;
            Kcf = 0.00000001;
            qnom = 0.001;
            ph = 500000;
            pnom = 7e6f;

            mpP1 = addPowerPort("P1", "NodeHydraulic");
            mpP2 = addPowerPort("P2", "NodeHydraulic");
            mpIn = addReadPort("in", "NodeSignal", Port::NotRequired);
            mpOut = addWritePort("xv", "NodeSignal", Port::NotRequired);

            registerParameter("p_max", "Maximum opening pressure", "[Pa]", pmax);
            registerParameter("tao", "Time Constant of Spool", "[s]", tao);
            registerParameter("k_cs", "Steady State Characteristic due to Spring", "[(m^3/s)/Pa]", Kcs);
            registerParameter("k_cf", "Steady State Characteristic due to Flow Forces", "[(m^3/s)/Pa]", Kcf);
            registerParameter("q_nom", "Flow with Fully Open Valve and pressure drop Pnom", "[m^3/s]", qnom);
            registerParameter("p_h", "Hysteresis Width", "[Pa]", ph);
        }


        void initialize()
        {
            mpND_in = getSafeNodeDataPtr(mpIn, NodeSignal::Value, 1);
            mpND_out = getSafeNodeDataPtr(mpOut, NodeSignal::Value, 0);

            mpND_p1 = getSafeNodeDataPtr(mpP1, NodeHydraulic::Pressure);
            mpND_q1 = getSafeNodeDataPtr(mpP1, NodeHydraulic::Flow);
            mpND_c1 = getSafeNodeDataPtr(mpP1, NodeHydraulic::WaveVariable);
            mpND_Zc1 = getSafeNodeDataPtr(mpP1, NodeHydraulic::CharImpedance);

            mpND_p2 = getSafeNodeDataPtr(mpP2, NodeHydraulic::Pressure);
            mpND_q2 = getSafeNodeDataPtr(mpP2, NodeHydraulic::Flow);
            mpND_c2 = getSafeNodeDataPtr(mpP2, NodeHydraulic::WaveVariable);
            mpND_Zc2 = getSafeNodeDataPtr(mpP2, NodeHydraulic::CharImpedance);

            x0 = 0.00001;
            mPrevX0 = 0;
            x0max = qnom / sqrt(pnom);
            Cs = sqrt(pnom) / Kcs;
            Cf = 1.0 / (Kcf*sqrt(pnom));

            double wCutoff = 1 / tao;
            double num[2] = {1.0, 0.0};
            double den[2] = {1.0, 1.0/wCutoff};
            mFilterLP.initialize(mTimestep, num, den, 0.0, 0.0, 0.0, x0max);
        }


        void simulateOneTimestep()
        {
            double in, p1, q1, c1, Zc1, p2, q2, c2, Zc2;
            double b1, gamma, b2, xs, xh, xsh, wCutoff;
            bool cav = false;

            //Get variable values from nodes
            p1 = (*mpND_p1);
            q1 = (*mpND_q1);
            c1 = (*mpND_c1);
            Zc1 = (*mpND_Zc1);
            p2 = (*mpND_p2);
            q2 = (*mpND_q2);
            c2 = (*mpND_c2);
            Zc2 = (*mpND_Zc2);
            in = (*mpND_in);

            //PRV Equations

            limitValue(in, 0, 1);

            //Help variable b1
            b1 = Cs + (p1-p2)*Cf;
            if ( (p1-p2)*Cf < 0.0 )
            {
                b1 = Cs;
            }

            //Help variable gamma
            if (p1>p2)
            {
                if ( (sqrt(p1-p2)*2.0 + (Zc1+Zc2)*x0) != 0.0 )
                {
                    gamma = sqrt(p1-p2)*2.0 / (sqrt(p1-p2)*2.0 + (Zc1+Zc2)*x0);
                }
                else
                {
                    gamma = 1.0;
                }
            }
            else
            {
                if ( (sqrt(p2-p1)*2.0 + (Zc1+Zc2)*x0) != 0.0 )
                {
                    gamma = sqrt(p2-p1)*2.0 / (sqrt(p2-p1)*2.0 + (Zc1+Zc2)*x0);
                }
                else
                {
                    gamma = 1.0;
                }
            }

            //Help variable b2
            if (p1 > p2)
            {
                b2 = gamma*(Zc1+Zc2)*sqrt(p1-p2);
            }
            else
            {
                b2 = gamma*(Zc1+Zc2)*sqrt(p2-p1);
            }
            if (b2 < 0.0)
            {
                b2 = 0.0;
            }

            // Calculation of spool position
            xs = (gamma*(c1) + b2*x0/2.0 - pmax*in) / (b1+b2);

            //Hysteresis
            xh = ph / (b1+b2);                                  //Hysteresis width [m]
            xsh = mHyst.getValue(xs, xh, mPrevX0);

            //Filter
            wCutoff = (1.0 + b2/b1) * 1.0/tao;                //Cutoff frequency
            double num[2] = {1.0, 0.0};
            double den[2] = {1.0, 1.0/wCutoff};
            mFilterLP.setNumDen(num,den);
            mFilterLP.update(xsh);
            x0 = mFilterLP.value();

            //Turbulent flow equation
            mTurb.setFlowCoefficient(x0);
            q2 = mTurb.getFlow(c1,c2,Zc1,Zc2);
            q1 = -q2;
            p2 = c2+Zc2*q2;
            p1 = c1+Zc1*q1;

            // Cavitation
            if (p1 < 0.0)
            {
                c1 = 0.0;
                Zc1 = 0.0;
                cav = true;
            }
            if (p2 < 0.0)
            {
                c2 = 0.0;
                Zc2 = 0.0;
                cav = true;
            }
            if (cav)
            {
                xs = (c1 + b2*x0/2.0 - pmax*in) / (b1+b2);
                xsh = mHyst.getValue(xs, xh, mPrevX0);
                x0 = mFilterLP.value();        //! @todo Make the filter actually redo last step if possible; this will create an undesired delay of one iteration

                mTurb.setFlowCoefficient(x0);
                q2 = mTurb.getFlow(c1,c2,Zc1,Zc2);
                q1 = -q2;
                p2 = c2+Zc2*q2;
                p1 = c1+Zc1*q1;

                if (p1 < 0.0) { p1 = 0.0; }
                if (p2 < 0.0) { p2 = 0.0; }
            }

            mPrevX0 = x0;

            //Write new variables to nodes
            (*mpND_p1) = p1;
            (*mpND_q1) = q1;
            (*mpND_p2) = p2;
            (*mpND_q2) = q2;
            (*mpND_out) = x0;
        }
    };
}

#endif // HYDRAULICPRESSURERELIEFVALVE_HPP_INCLUDED
