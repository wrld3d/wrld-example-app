// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinCreation.h"
#include "MyPinCreationDetails.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationConfirmationController: private Eegeo::NonCopyable
            {
            public:

                MyPinCreationConfirmationController(const std::shared_ptr<IMyPinCreationConfirmationViewModel>& viewModel,
                                                    const std::shared_ptr<IMyPinCreationConfirmationView>& view,
                                                    const std::shared_ptr<MyPinCreationDetails::View::IMyPinCreationDetailsViewModel>& detailsViewModel,
                                                    const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                    const std::shared_ptr<Metrics::IMetricsService>& metricsService);
                
                ~MyPinCreationConfirmationController();

            private:

                void OnDismissed();
                void OnConfirmed();
                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state);

                const std::shared_ptr<IMyPinCreationConfirmationViewModel> m_viewModel;
                const std::shared_ptr<IMyPinCreationConfirmationView> m_view;
                const std::shared_ptr<MyPinCreationDetails::View::IMyPinCreationDetailsViewModel> m_detailsViewModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;

                Eegeo::Helpers::TCallback2<MyPinCreationConfirmationController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationConfirmationController> m_dismissedCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationConfirmationController> m_confirmedCallback;
                
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;
            };
        }
    }
}
