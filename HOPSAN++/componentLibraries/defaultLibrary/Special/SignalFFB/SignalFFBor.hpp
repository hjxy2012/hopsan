#ifndef SIGNALFFBOR_HPP_INCLUDED
#define SIGNALFFBOR_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include "math.h"

//!
//! @file SignalFFBor.hpp
//! @author Petter Krus <petter.krus@liu.se>
//! @date Fri 24 Aug 2012 10:28:19
//! @brief FFBD OR out
//! @ingroup SignalComponents
//!
//This component is generated by COMPGEN for HOPSAN-NG simulation 
//from 
/*{, C:, Documents and Settings, petkr14, My Documents, \
CompgenNG}/FFBDcomponentsNG.nb*/

using namespace hopsan;

class SignalFFBor : public ComponentSignal
{
private:
     double min0;
     double min1;
     Port *mpPin0;
     Port *mpPin1;
     Port *mpPstate;
     Port *mpPexiting;
     int mNstep;
     //inputVariables
     double in0;
     double in1;
     //outputVariables
     double state;
     double exiting;
     //Expressions variables
     double state0;
     double state1;
     double oldState0;
     double oldState1;
     double oldIn0;
     double oldIn1;
     double oldExiting;
     //Delay declarations
     //inputVariables pointers
     double *mpND_in0;
     double *mpND_in1;
     //outputVariables pointers
     double *mpND_state;
     double *mpND_exiting;
     EquationSystemSolver *mpSolver;

public:
     static Component *Creator()
     {
        return new SignalFFBor();
     }

     void configure()
     {
        const double in0 = 0.;
        const double in1 = 0.;

        mNstep=9;
        min0 = in0;
        min1 = in1;

        //Add ports to the component

        //Add inputVariables ports to the component
        mpPin0=addReadPort("Pin0","NodeSignal", Port::NotRequired);
        mpPin1=addReadPort("Pin1","NodeSignal", Port::NotRequired);

        //Add outputVariables ports to the component
        mpPstate=addWritePort("Pstate","NodeSignal", Port::NotRequired);
        mpPexiting=addWritePort("Pexiting","NodeSignal", Port::NotRequired);

        //Register changable parameters to the HOPSAN++ core
        registerParameter("in0", "Input 0", "", min0);
        registerParameter("in1", "Input 1", "", min1);
     }

    void initialize()
     {
        //Read port variable pointers from nodes
        //Read inputVariables pointers from nodes
        mpND_in0=getSafeNodeDataPtr(mpPin0, NodeSignal::Value,min0);
        mpND_in1=getSafeNodeDataPtr(mpPin1, NodeSignal::Value,min1);
        //Read outputVariable pointers from nodes
        mpND_state=getSafeNodeDataPtr(mpPstate, NodeSignal::Value);
        mpND_exiting=getSafeNodeDataPtr(mpPexiting, NodeSignal::Value);

        //Read variables from nodes

        //Read inputVariables from nodes
        in0 = (*mpND_in0);
        in1 = (*mpND_in1);

        //Read outputVariables from nodes
        state = mpPstate->getStartValue(NodeSignal::Value);
        exiting = mpPexiting->getStartValue(NodeSignal::Value);

        //InitialExpressions
        oldIn0 = in0;
        oldIn1 = in1;
        oldExiting = exiting;


        //Initialize delays

     }
    void simulateOneTimestep()
     {
        //Read variables from nodes

        //Read inputVariables from nodes
        in0 = (*mpND_in0);
        in1 = (*mpND_in1);

        //LocalExpressions

          //Expressions
          state0 = onPositive(-0.5 - onPositive(-0.5 + oldExiting) + \
2*onPositive(-0.5 + in0 - oldIn0) + onPositive(-0.5 + oldState0));
          state1 = onPositive(-0.5 - onPositive(-0.5 + oldExiting) + \
2*onPositive(-0.5 + in1 - oldIn1) + onPositive(-0.5 + oldState1));
          exiting = onPositive(-0.5 + oldState0 + oldState1);
          state = onPositive(-0.5 + onPositive(-0.5 + state0) + \
onPositive(-0.5 + state1));
          oldState0 = state0;
          oldState1 = state1;
          oldIn0 = in0;
          oldIn1 = in1;
          oldExiting = exiting;

        //Calculate the delayed parts


        //Write new values to nodes
        //outputVariables
        (*mpND_state)=state;
        (*mpND_exiting)=exiting;

        //Update the delayed variabels

     }
};
#endif // SIGNALFFBOR_HPP_INCLUDED
