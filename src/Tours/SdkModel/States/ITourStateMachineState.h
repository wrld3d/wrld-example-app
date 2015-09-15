// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace States
            {
                class ITourStateMachineState
                {
                public:
                    virtual ~ITourStateMachineState() { }
                    
                    virtual void Enter() = 0;
                    
                    virtual void Update(float dt) = 0;
                    
                    virtual void Exit() = 0;
                };
            }
        }
    }
}