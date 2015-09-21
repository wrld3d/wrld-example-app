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
                class ITourStateMachine
                {
                public:
                    virtual ~ITourStateMachine() { }
                    
                    virtual void StartTour(const int atCard) = 0;
                    
                    virtual void ChangeToState(int activeStateIndex) = 0;
                    
                    virtual void Update(float dt) = 0;
                    
                    virtual void EndTour() = 0;
                    
                    virtual const int GetCurrentState() const = 0;
                };
            }
        }
    }
}