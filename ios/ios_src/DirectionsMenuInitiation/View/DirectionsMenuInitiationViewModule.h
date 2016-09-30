// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Metrics.h"
#include "Rendering.h"
#include "BidirectionalBus.h"
#include "DirectionsMenuInitiation.h"
#include "IDirectionsMenuInitiationViewModule.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace View
        {
            class DirectionsMenuInitiationViewModule: public IDirectionsMenuInitiationViewModule, private Eegeo::NonCopyable
            {
            private:
                DirectionsMenuInitiationController* m_pController;
                DirectionsMenuInitiationView* m_pView;
                DirectionInitiationStateChangedObserver* m_pObserver;

            public:
                DirectionsMenuInitiationViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                                  IDirectionsMenuInitiationViewModel& viewModel,
                                                  const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                  Metrics::IMetricsService& metricsService);

                ~DirectionsMenuInitiationViewModule();

                DirectionsMenuInitiationController& GetDirectionsMenuInitiationController() const;

                DirectionsMenuInitiationView& GetDirectionsMenuInitiationView() const;
            };
        }
    }
}
