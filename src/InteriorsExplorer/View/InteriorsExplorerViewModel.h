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
            class InteriorsExplorerViewModel : public ScreenControl::View::IMultiStateScreenControlViewModel
            {
            public:
                InteriorsExplorerViewModel(bool initiallyOnScreen,
                                           Eegeo::Helpers::TIdentity identity,
                                           ExampleAppMessaging::TMessageBus& messageBus);
                
                ~InteriorsExplorerViewModel();
                
                Eegeo::Helpers::TIdentity GetIdentity() const override;

                enum DisplayMode {Default, Navigation};
                
                void AddToScreen() override;
                
                void RemoveFromScreen() override;

                void InsertOnScreenStateChangedCallback(
                        Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback) override;
                
                void RemoveOnScreenStateChangedCallback(
                        Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback) override;
                
                bool IsOffScreen() const override;
                
                bool IsOnScreen() const override;

                ScreenControl::View::IMultiStateScreenControlViewModel& GetScreenControlViewModel();

                void SetState(ScreenControl::View::TScreenControlViewState state) override;

                ScreenControl::View::TScreenControlViewState GetState() override;

            private:
                Eegeo::Helpers::TIdentity m_identity;
                
                bool m_isOnScreen;
                bool m_canAddToScreen;

                ScreenControl::View::TScreenControlViewState m_viewState;
                
                Eegeo::Helpers::CallbackCollection1<IScreenControlViewModel&> m_onScreenStateChangedCallbacks;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<InteriorsExplorerViewModel, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
            };
        }
    }
}
