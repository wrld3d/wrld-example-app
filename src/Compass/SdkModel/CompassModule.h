// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Hypodermic/ContainerBuilder.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class CompassModule
            {
            public:
                CompassModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder);
                
                void Register();
            private:
                const std::shared_ptr<Hypodermic::ContainerBuilder> m_builder;
            };
            /*
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
                              InteriorsNavigation::SdkModel::IInteriorsNavigationService& interiorsNavigationService,
                              Eegeo::Location::ILocationService& locationService,
                              ExampleApp::AppCamera::SdkModel::IAppCameraController& cameraController,
                              Eegeo::Helpers::IIdentityProvider& identityProvider,
                              ExampleAppMessaging::TMessageBus& messageBus,
                              Metrics::IMetricsService& metricsService,
                              InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorExplorerModel,
                              AppModes::SdkModel::IAppModeModel& appModeModel,
                              Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory);

                ~CompassModule();

                ICompassModel& GetCompassModel() const;

                View::ICompassViewModel& GetCompassViewModel() const;

                ICompassUpdateController& GetCompassUpdateController() const;

                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;
            };*/
        }
    }
}
