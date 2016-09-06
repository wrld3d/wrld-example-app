// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "IFlattenButtonView.h"
#include "IFlattenButtonViewModel.h"
#include "ApplyScreenControl.h"
#include "MyPinCreationStateChangedMessage.h"
#include "IMetricsService.h"
#include "AppModeChangedMessage.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            class FlattenButtonController : private Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<IFlattenButtonViewModel> m_viewModel;
                const std::shared_ptr<IFlattenButtonView> m_view;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;

                Eegeo::Helpers::TCallback1<FlattenButtonController, const FlattenButtonModelStateChangedMessage&> m_stateChangeHandler;
                Eegeo::Helpers::TCallback1<FlattenButtonController, bool> m_toggledCallback;
                Eegeo::Helpers::TCallback2<FlattenButtonController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                Eegeo::Helpers::TCallback1<FlattenButtonController, const MyPinCreation::MyPinCreationStateChangedMessage&> m_myPinCreationStateChangedMessageHandler;
                Eegeo::Helpers::TCallback1<FlattenButtonController, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;
                
                bool m_appModeAllowsOpen;
                
                void OnToggleButton(bool& toggle);

                void OnFlattenButtonModelStateChangedMessage(const FlattenButtonModelStateChangedMessage& message);

                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state);
                
                void OnMyPinCreationStateChangedMessage(const MyPinCreation::MyPinCreationStateChangedMessage& message);

                void OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message);

            public:
                FlattenButtonController(
                                        const std::shared_ptr<IFlattenButtonViewModel>& viewModel,
                                        const std::shared_ptr<IFlattenButtonView>& view,
                                        const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                        const std::shared_ptr<Metrics::IMetricsService>& metricsService
                );

                ~FlattenButtonController();
            };
        }
    }
}
