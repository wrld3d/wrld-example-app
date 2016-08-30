// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "IStateMachineState.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace SdkModel
        {
            class IAppModeStatesFactory
            {
            public:
                virtual ~IAppModeStatesFactory()
                {
                    
                }
                
                virtual const std::vector<Helpers::IStateMachineState*> CreateStateMachineStates() = 0;
            };
        }
    }
}
