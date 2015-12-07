// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "StateMachine.h"

namespace ExampleApp
{
    namespace Helpers
    {
        StateMachine::StateMachine(const std::vector<IStateMachineState*>& states)
        : m_states(states)
        , m_currentState(-1)
        {
        }
        
        StateMachine::~StateMachine()
        {
            
        }
        
        void StateMachine::StartStateMachine(int startingStateIndex)
        {
            Eegeo_ASSERT(startingStateIndex < m_states.size(), "Invalid starting state");

            m_currentState = startingStateIndex;
            const int previousState = -1;
            
            m_states[m_currentState]->Enter(previousState);
        }
        
        void StateMachine::ChangeToState(int activeStateIndex)
        {
            Eegeo_ASSERT(activeStateIndex < m_states.size(), "Invalid state");
            
            m_states[m_currentState]->Exit(activeStateIndex);
            
            int previousState = m_currentState;
            m_currentState = activeStateIndex;
            
            m_states[m_currentState]->Enter(previousState);
            
        }
        
        void StateMachine::Update(float dt)
        {
            Eegeo_ASSERT(m_currentState >= 0, "No state has been selected");
            m_states[m_currentState]->Update(dt);
        }
        
        void StateMachine::StopStateMachine()
        {
            Eegeo_ASSERT(m_currentState >= 0, "No state has been selected");
            const int nextState = -1;
            m_states[m_currentState]->Exit(nextState);
            
            m_currentState = nextState;
        }
        
        int StateMachine::GetCurrentStateIndex()
        {
            return m_currentState;
        }
    }
}