#ifndef PNEUMATICDESENSOR_HPP_INCLUDED
#define PNEUMATICDESENSOR_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include "math.h"

//!
//! @file PneumaticdEsensor.hpp
//! @author Petter Krus <petter.krus@liu.se>
//! @date Wed 13 Mar 2013 16:55:00
//! @brief Pneumatic energy flow sensor
//! @ingroup PneumaticComponents
//!
//==This code has been autogenerated using Compgen==
//from 
/*{, C:, Users, petkr14.IEI, Documents, CompgenNG}/PneumaticNGM.nb*/

using namespace hopsan;

class PneumaticdEsensor : public ComponentSignal
{
private:
     Port *mpPp1;
     Port *mpPdEsensor;
     int mNstep;
     //Port Pp1 variable
     double pp1;
     double qmp1;
     double Tp1;
     double dEp1;
     double cp1;
     double Zcp1;
//==This code has been autogenerated using Compgen==
     //inputVariables
     //outputVariables
     double dEsensor;
     //Expressions variables
     //Port Pp1 pointer
     double *mpND_pp1;
     double *mpND_qmp1;
     double *mpND_Tp1;
     double *mpND_dEp1;
     double *mpND_cp1;
     double *mpND_Zcp1;
     //Delay declarations
//==This code has been autogenerated using Compgen==
     //inputVariables pointers
     //outputVariables pointers
     double *mpND_dEsensor;
     EquationSystemSolver *mpSolver;

public:
     static Component *Creator()
     {
        return new PneumaticdEsensor();
     }

     void configure()
     {
//==This code has been autogenerated using Compgen==

        mNstep=9;

        //Add ports to the component
        mpPp1=addReadPort("Pp1","NodePneumatic");

        //Add inputVariables ports to the component

        //Add outputVariables ports to the component
        mpPdEsensor=addWritePort("PdEsensor","NodeSignal", \
Port::NOTREQUIRED);

//==This code has been autogenerated using Compgen==
        //Register changable parameters to the HOPSAN++ core
        //Set start values in nodes
        //Port Pp1
        setStartValue(mpPp1, NodePneumatic::Pressure,100000.);
        setStartValue(mpPp1, NodePneumatic::MassFlow,0.);
        setStartValue(mpPp1, NodePneumatic::Temperature,293.);
        setStartValue(mpPp1, NodePneumatic::EnergyFlow,0.);
        setStartValue(mpPp1, NodePneumatic::WaveVariable,0.);
        setStartValue(mpPp1, NodePneumatic::CharImpedance,0.);
     }

    void initialize()
     {
        //Read port variable pointers from nodes
        //Port Pp1
        mpND_pp1=getSafeNodeDataPtr(mpPp1, NodePneumatic::Pressure);
        mpND_qmp1=getSafeNodeDataPtr(mpPp1, NodePneumatic::MassFlow);
        mpND_Tp1=getSafeNodeDataPtr(mpPp1, NodePneumatic::Temperature);
        mpND_dEp1=getSafeNodeDataPtr(mpPp1, NodePneumatic::EnergyFlow);
        mpND_cp1=getSafeNodeDataPtr(mpPp1, NodePneumatic::WaveVariable);
        mpND_Zcp1=getSafeNodeDataPtr(mpPp1, NodePneumatic::CharImpedance);
        //Read inputVariables pointers from nodes
        //Read outputVariable pointers from nodes
        mpND_dEsensor=getSafeNodeDataPtr(mpPdEsensor, NodeSignal::Value);

        //Read variables from nodes
        //Port Pp1
        pp1 = (*mpND_pp1);
        qmp1 = (*mpND_qmp1);
        Tp1 = (*mpND_Tp1);
        dEp1 = (*mpND_dEp1);
        cp1 = (*mpND_cp1);
        Zcp1 = (*mpND_Zcp1);

        //Read inputVariables from nodes

        //Read outputVariables from nodes
        dEsensor = mpPdEsensor->getStartValue(NodeSignal::Value);

//==This code has been autogenerated using Compgen==


        //Initialize delays

     }
    void simulateOneTimestep()
     {
        //Read variables from nodes
        //Port Pp1
        pp1 = (*mpND_pp1);
        qmp1 = (*mpND_qmp1);
        Tp1 = (*mpND_Tp1);
        dEp1 = (*mpND_dEp1);
        cp1 = (*mpND_cp1);
        Zcp1 = (*mpND_Zcp1);

        //Read inputVariables from nodes

        //LocalExpressions

          //Expressions
          dEsensor = dEp1;

        //Calculate the delayed parts


        //Write new values to nodes
        //Port Pp1
        //outputVariables
        (*mpND_dEsensor)=dEsensor;

        //Update the delayed variabels

     }
};
#endif // PNEUMATICDESENSOR_HPP_INCLUDED
