// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "ITourStateMachine.h"
#include "Tours.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace States
            {
                class TourStateMachine : public ITourStateMachine, private Eegeo::NonCopyable
                {
                    std::vector<ITourStateMachineState*> m_states;
                    ITourStateMachineState* m_pTourSetupTeardownState;
                    int m_currentState;
                    
                public:
                    // TourStateMachine takes ownership of states and assumes they are dynamically allocated by Eegeo_NEW
                    TourStateMachine(const std::vector<ITourStateMachineState*>& states,
                                     ITourStateMachineState* pTourSetupTeardownState);
                    
                    ~TourStateMachine();
                    
                    void StartTour(const int atCard);
                    
                    void ChangeToState(int activeStateIndex);
                    
                    void Update(float dt);
                    
                    void EndTour();
                    
                    const int GetCurrentState() const { return m_currentState; }
                };
            }
        }
    }
}
