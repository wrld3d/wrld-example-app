// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "MyPinCreationScreenControl.h"
#include "IAppModeModel.h"
#include "IIdentity.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "MyPinCreation.h"
#include "CallbackCollection.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationInitiationViewModel : public IMyPinCreationInitiationViewModel, private Eegeo::NonCopyable
            {
            public:

                MyPinCreationInitiationViewModel(Eegeo::Helpers::TIdentity identity,
                                                 bool isInitiallyOnScreen,
                                                 ExampleAppMessaging::TMessageBus& messageBus);
                ~MyPinCreationInitiationViewModel();

                Eegeo::Helpers::TIdentity GetIdentity() const;

                void AddToScreen();

                void RemoveFromScreen();

                void UpdateOnScreenState(float onScreenState);

                void InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback);

                void RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback);

                bool IsFullyOffScreen() const;

                bool IsFullyOnScreen() const;

                float OnScreenState() const;
                
                bool IsAddedToScreen() const;

                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel();

                bool ShouldOffsetViewButton() const;

                void SetShouldOffsetViewButton(bool shouldOffset);

            private:
                MyPinCreationScreenControl m_screenControl;
                bool m_shouldOffsetViewButton;
                bool m_canAddToScreen;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<MyPinCreationInitiationViewModel, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;

                void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);
            };
        }
    }
}
