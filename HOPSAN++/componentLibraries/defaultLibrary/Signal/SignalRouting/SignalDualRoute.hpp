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
//! @file   SignalDualRoute.hpp
//! @author Robert Braun <bjorn.eriksson@liu.se>
//! @date   2011-08-29
//!
//! @brief Contains a signal routering component with two inputs
//!
//$Id$

#ifndef SIGNALDUALROUTE_HPP_INCLUDED
#define SIGNALDUALROUTE_HPP_INCLUDED

#include "ComponentEssentials.h"

namespace hopsan {

    //!
    //! @brief
    //! @ingroup SignalComponents
    //!
    class SignalDualRoute : public ComponentSignal
    {

    private:
        double *mpND_route;
        double *mpND_in1;
        double *mpND_in2;
        double *mpND_out;

    public:
        static Component *Creator()
        {
            return new SignalDualRoute();
        }

        void configure()
        {
            addInputVariable("in1", "", "", 0, &mpND_in1);
            addInputVariable("in2", "", "", 0, &mpND_in2);
            addInputVariable("route", "Input selection", "", 0, &mpND_route);
            addOutputVariable("out", "Selected input", "", &mpND_out);
        }


        void initialize()
        {

        }


        void simulateOneTimestep()
        {
            if((*mpND_route) < 1.5 )
            {
                (*mpND_out) = (*mpND_in1);
            }
            else
            {
                (*mpND_out) = (*mpND_in2);
            }
        }
    };
}
#endif
