// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinCreation.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "AppModeChangedMessage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationInitiationController : private Eegeo::NonCopyable
            {
            public:
                MyPinCreationInitiationController(const std::shared_ptr<IMyPinCreationInitiationViewModel>& viewModel,
                                                  const std::shared_ptr<IMyPinCreationInitiationView>& view,
                                                  const std::shared_ptr<IMyPinCreationConfirmationViewModel>& confirmationViewModel,
                                                  const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                  const std::shared_ptr<Metrics::IMetricsService>& metricsService);
                
                ~MyPinCreationInitiationController();

                void OnSelected();
                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state);

            private:

                const std::shared_ptr<IMyPinCreationInitiationViewModel> m_viewModel;
                const std::shared_ptr<IMyPinCreationInitiationView> m_view;
                const std::shared_ptr<IMyPinCreationConfirmationViewModel> m_confirmationViewModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;
                
                Eegeo::Helpers::TCallback2<MyPinCreationInitiationController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationInitiationController> m_selectedCallback;
                
                Eegeo::Helpers::TCallback1<MyPinCreationInitiationController, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;
                void OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message);
                
                bool m_appModeAllowsOpen;
            };
        }
    }
}
