// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include <vector>
#include "IStateMachineState.h"

namespace ExampleApp
{
    namespace Helpers
    {
        class StateMachine : private Eegeo::NonCopyable
        {
        private:
            
            const std::vector<IStateMachineState*>& m_states;
            int m_currentState;
            
        public:
            
            StateMachine(const std::vector<IStateMachineState*>& m_states);
            
            ~StateMachine();
            
            void StartStateMachine(int startingStateIndex);
            
            void ChangeToState(int activeStateIndex);
            
            void Update(float dt);
            
            void StopStateMachine();
            
            int GetCurrentStateIndex();
            
        };
    }
}