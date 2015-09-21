// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourStateMachine.h"
#include "ITourStateMachineState.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace States
            {
                TourStateMachine::TourStateMachine(const std::vector<ITourStateMachineState*>& states,
                                                   ITourStateMachineState* pTourSetupTeardownState)
                : m_states(states)
                , m_pTourSetupTeardownState(pTourSetupTeardownState)
                , m_currentState(-1)
                {
                    
                }
                
                TourStateMachine::~TourStateMachine()
                {
                    for(size_t i = 0; i < m_states.size(); ++ i)
                    {
                        Eegeo_DELETE m_states[i];
                    }
                    
                    m_states.clear();
                    
                    Eegeo_DELETE m_pTourSetupTeardownState;
                }
                
                void TourStateMachine::StartTour(const int atCard)
                {
                    if(m_pTourSetupTeardownState != NULL)
                    {
                        m_pTourSetupTeardownState->Enter();
                    }
                    
                    m_currentState = atCard;
                    m_states[m_currentState]->Enter();
                }
                
                void TourStateMachine::ChangeToState(int activeStateIndex)
                {
                    if(m_currentState != activeStateIndex)
                    {
                        m_states[m_currentState]->Exit();
                        m_currentState = activeStateIndex;
                        m_states[m_currentState]->Enter();
                    }
                }
                
                void TourStateMachine::Update(float dt)
                {
                    m_states[m_currentState]->Update(dt);
                }
                
                void TourStateMachine::EndTour()
                {
                    m_states[m_currentState]->Exit();
                    m_currentState = -1;
                    
                    if(m_pTourSetupTeardownState != NULL)
                    {
                        m_pTourSetupTeardownState->Exit();
                    }
                }
            }
        }
    }
}
