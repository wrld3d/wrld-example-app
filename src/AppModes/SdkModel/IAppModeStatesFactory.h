// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include <vector>
#include "IStateMachineState.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace SdkModel
        {
            class IAppModeStatesFactory : protected Eegeo::NonCopyable
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
