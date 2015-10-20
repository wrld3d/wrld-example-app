// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Compass.h"
#include "ICompassModule.h"
#include "Rendering.h"
#include "GlobeCamera.h"
#include "IIdentity.h"
#include "Location.h"
#include "CompassModeObserver.h"
#include "CompassViewCycledObserver.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "AppModes.h"
#include "AlertBox.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class CompassModule : public ICompassModule, private Eegeo::NonCopyable
            {
            private:
                View::CompassViewModel* m_pViewModel;
                ICompassModel* m_pModel;
                ICompassUpdateController* m_pCompassUpdateController;
                CompassModeObserver* m_pCompassModeObserver;
                CompassViewCycledObserver* m_pCompassViewCycledObserver;

            public:
                CompassModule(Eegeo::Location::NavigationService& navigationService,
                              Eegeo::Location::ILocationService& locationService,
                              Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController,
                              Eegeo::Helpers::IIdentityProvider& identityProvider,
                              ExampleAppMessaging::TMessageBus& messageBus,
                              Metrics::IMetricsService& metricsService,
                              AppModes::SdkModel::IAppModeModel& appModeModel,
                              Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory);

                ~CompassModule();

                ICompassModel& GetCompassModel() const;

                View::ICompassViewModel& GetCompassViewModel() const;

                ICompassUpdateController& GetCompassUpdateController() const;

                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;
            };
        }
    }
}
