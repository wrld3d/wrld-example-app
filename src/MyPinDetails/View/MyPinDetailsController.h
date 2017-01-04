// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinDetails.h"
#include "BidirectionalBus.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            class MyPinDetailsController : private Eegeo::NonCopyable
            {
            public:

                MyPinDetailsController(IMyPinDetailsView& view, IMyPinDetailsViewModel& viewModel, ExampleAppMessaging::TMessageBus& messageBus);
                ~MyPinDetailsController();

            private:

                void OnOpened();
                void OnClosed();

                void OnDismissed();
                void OnRemovePin();

                void OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message);

                IMyPinDetailsView& m_view;
                IMyPinDetailsViewModel& m_viewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback0<MyPinDetailsController> m_viewModelOpenedCallback;
                Eegeo::Helpers::TCallback0<MyPinDetailsController> m_viewModelClosedCallback;

                Eegeo::Helpers::TCallback0<MyPinDetailsController> m_viewRemovePinCallback;
                Eegeo::Helpers::TCallback0<MyPinDetailsController> m_viewDismissedCallback;

                Eegeo::Helpers::TCallback1<MyPinDetailsController, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;
            };
        }
    }
}
