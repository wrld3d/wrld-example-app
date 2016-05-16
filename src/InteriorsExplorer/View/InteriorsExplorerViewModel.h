// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ScreenControlViewModelBase.h"
#include "IIdentity.h"
#include "IAppModeModel.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "AppModeChangedMessage.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorsExplorerViewModel : public ScreenControl::View::IScreenControlViewModel
            {
            public:
                InteriorsExplorerViewModel(bool initiallyOnScreen,
                                           Eegeo::Helpers::TIdentity identity,
                                           ExampleAppMessaging::TMessageBus& messageBus);
                
                ~InteriorsExplorerViewModel();
                
                Eegeo::Helpers::TIdentity GetIdentity() const;
                
                void AddToScreen();
                
                void RemoveFromScreen();
                
                void UpdateOnScreenState(float onScreenState);
                
                void InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<IScreenControlViewModel&, float>& callback);
                
                void RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<IScreenControlViewModel&, float>& callback);
                
                bool IsFullyOffScreen() const;
                
                bool IsFullyOnScreen() const;
                
                float OnScreenState() const;
                
                bool IsAddedToScreen() const;
                
            private:
                Eegeo::Helpers::TIdentity m_identity;
                
                float m_onScreenState;
                bool m_addedToScreen;
                bool m_canAddToScreen;
                
                Eegeo::Helpers::CallbackCollection2<IScreenControlViewModel&, float> m_onScreenStateChangedCallbacks;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<InteriorsExplorerViewModel, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
            };
        }
    }
}