// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "AppModeModel.h"
#include "InteriorSelectionModel.h"
#include "AppModeChangedMessage.h"
#include "TourService.h"
#include "WorldState.h"
#include "InteriorExplorerState.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace SdkModel
        {
            AppModeModel::AppModeModel(ExampleAppMessaging::TMessageBus& messageBus)
            : m_messageBus(messageBus)
            , m_appMode(WorldMode)
            , m_previousAppMode(WorldMode)
            , m_pStateMachine(NULL)
            , m_switchAppMode(false)
            {
                
            }

            AppModeModel::~AppModeModel()
            {
                
                if(m_pStateMachine != NULL)
                {
                    m_pStateMachine->StopStateMachine();
                    Eegeo_DELETE m_pStateMachine;
                    m_pStateMachine = NULL;
                    
                    for(int i = 0; i < m_appStates.size(); ++i)
                    {
                        Eegeo_DELETE m_appStates[i];
                    }
                }
                m_appStates.clear();
            }
            

            void AppModeModel::RegisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_appModeChangedCallbacks.AddCallback(callback);
            }

            void AppModeModel::UnregisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_appModeChangedCallbacks.RemoveCallback(callback);
            }

            AppMode AppModeModel::GetAppMode() const
            {
                return m_appMode;
            }

            void AppModeModel::SetAppMode(AppMode appMode)
            {
                if (m_appMode != appMode)
                {
                    m_previousAppMode = m_appMode;
                    
                    m_appMode = appMode;
                    m_switchAppMode = true;
                }
            }
            
            void AppModeModel::Update(float dt)
            {
                Eegeo_ASSERT(m_pStateMachine != NULL, "State Machine not initialised");
                
                if (m_switchAppMode)
                {
                    m_switchAppMode = false;
                    
                    m_appModeChangedCallbacks.ExecuteCallbacks();
                    m_messageBus.Publish(AppModeChangedMessage(m_appMode));
                    m_pStateMachine->ChangeToState(m_appMode);
                }
                
                m_pStateMachine->Update(dt);
            }
            
            void AppModeModel::InitialiseStateMachine(const std::vector<Helpers::IStateMachineState*>& appStates)
            {
                Eegeo_ASSERT(m_pStateMachine == NULL, "Cannot initialise the state machine twice");
                
                m_appStates = appStates;
                
                m_pStateMachine = Eegeo_NEW(Helpers::StateMachine)(m_appStates);
                
                m_pStateMachine->StartStateMachine(WorldMode);
            }
        }
    }
}