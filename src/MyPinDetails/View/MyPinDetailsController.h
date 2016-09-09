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

                MyPinDetailsController(const std::shared_ptr<IMyPinDetailsView>& view,
                                       const std::shared_ptr<IMyPinDetailsViewModel>& viewModel,
                                       const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                ~MyPinDetailsController();

            private:

                void OnOpened();
                void OnClosed();

                void OnDismissed();
                void OnRemovePin();

                const std::shared_ptr<IMyPinDetailsView>& m_view;
                const std::shared_ptr<IMyPinDetailsViewModel>& m_viewModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus>& m_messageBus;

                Eegeo::Helpers::TCallback0<MyPinDetailsController> m_viewModelOpenedCallback;
                Eegeo::Helpers::TCallback0<MyPinDetailsController> m_viewModelClosedCallback;

                Eegeo::Helpers::TCallback0<MyPinDetailsController> m_viewRemovePinCallback;
                Eegeo::Helpers::TCallback0<MyPinDetailsController> m_viewDismissedCallback;
            };
        }
    }
}
