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
            
            virtual void Enter(int previousState) = 0;
            
            virtual void Update(float dt) = 0;
            
            virtual void Exit(int nextState) = 0;
        };
    }
}