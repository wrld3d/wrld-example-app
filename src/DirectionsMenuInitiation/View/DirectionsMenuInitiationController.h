// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "DirectionsMenuInitiation.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "AppModeChangedMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace View
        {
            class DirectionsMenuInitiationController : private Eegeo::NonCopyable
            {
            public:
                DirectionsMenuInitiationController(IDirectionsMenuInitiationViewModel& viewModel,
                                                  IDirectionsMenuInitiationView& view,
                                                  ExampleAppMessaging::TMessageBus& messageBus,
                                                  Metrics::IMetricsService& metricsService);
                
                ~DirectionsMenuInitiationController();

                void OnToggle(bool& toggle);
                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state);

            private:

                IDirectionsMenuInitiationViewModel& m_viewModel;
                IDirectionsMenuInitiationView& m_view;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Eegeo::Helpers::TCallback2<DirectionsMenuInitiationController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                Eegeo::Helpers::TCallback1<DirectionsMenuInitiationController, bool> m_selectedCallback;
                
                Eegeo::Helpers::TCallback1<DirectionsMenuInitiationController, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;
                void OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message);
                
                bool m_appModeAllowsOpen;
            };
        }
    }
}
