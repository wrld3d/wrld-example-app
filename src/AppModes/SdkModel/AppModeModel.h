// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IAppModeModel.h"
#include "Interiors.h"
#include "BidirectionalBus.h"
#include "StateMachine.h"
#include "IStateMachineState.h"
#include "AppCamera.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace SdkModel
        {
            class AppModeModel : public IAppModeModel
            {
            public:
                AppModeModel(ExampleAppMessaging::TMessageBus& messageBus);
                ~AppModeModel();

                
                void InitialiseStateMachine(const std::vector<Helpers::IStateMachineState*>& appStates);
                
                AppMode GetAppMode() const;
                
                void SetAppMode(AppMode appMode);
                
                void Update(float dt);

                void RegisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void UnregisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback);

            private:
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::CallbackCollection0 m_appModeChangedCallbacks;
                
                AppMode m_appMode;
                AppMode m_previousAppMode;
                
                Helpers::StateMachine* m_pStateMachine;
                std::vector<Helpers::IStateMachineState*> m_appStates;
                
                bool m_switchAppMode;
            };
        }
    }
}