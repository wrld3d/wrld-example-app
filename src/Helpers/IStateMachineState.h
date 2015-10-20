// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Helpers
    {
        class IStateMachineState
        {
        public:
            virtual ~IStateMachineState() { }
            
            virtual void Enter() = 0;
            
            virtual void Update(float dt) = 0;
            
            virtual void Exit() = 0;
        };
    }
}