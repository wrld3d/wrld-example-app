// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include "Types.h"
#include "ICompassModel.h"
#include "Rendering.h"
#include "CallbackCollection.h"
#include "AppCamera.h"
#include "Location.h"
#include "IMetricsService.h"
#include "AppModes.h"
#include "AlertBox.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "InteriorsNavigation.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class CompassModel : public ICompassModel, private Eegeo::NonCopyable
            {
                const std::shared_ptr<Eegeo::Location::NavigationService> m_navigationService;
                const std::shared_ptr<InteriorsNavigation::SdkModel::IInteriorsNavigationService> m_interiorsNavigationService;
                const std::shared_ptr<Eegeo::Location::ILocationService> m_locationService;
                const std::shared_ptr<ExampleApp::AppCamera::SdkModel::IAppCameraController> m_cameraController;
                Eegeo::Helpers::CallbackCollection0 m_compassAllowedChangedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_gpsModeChangedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_gpsModeUnauthorizedCallbacks;
                GpsMode::Values m_gpsMode;
                bool m_exitInteriorTriggered;
                std::map<Eegeo::Location::NavigationService::GpsMode, GpsMode::Values> m_compassGpsModeToNavigationGpsMode;
                std::map<GpsMode::Values, Eegeo::Location::NavigationService::GpsMode> m_navigationGpsModeToCompassGpsMode;
                std::map<GpsMode::Values, const char*> m_gpsModeToString;
                
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;

                const std::shared_ptr<AppModes::SdkModel::IAppModeModel> m_appModeModel;
                const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorsExplorerModel> m_interiorExplorerModel;
                Eegeo::Helpers::TCallback0<CompassModel> m_appModeChangedCallback;
                Eegeo::Helpers::TCallback0<CompassModel> m_interiorFloorChangedCallback;
                
                const std::shared_ptr<Eegeo::UI::NativeAlerts::IAlertBoxFactory> m_alertBoxFactory;
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<CompassModel> m_failAlertHandler;
                
            public:

                CompassModel(const std::shared_ptr<Eegeo::Location::NavigationService>& navigationService,
                             const std::shared_ptr<InteriorsNavigation::SdkModel::IInteriorsNavigationService>& interiorsNavigationService,
                             const std::shared_ptr<Eegeo::Location::ILocationService>& locationService,
                             const std::shared_ptr<ExampleApp::AppCamera::SdkModel::IAppCameraController>& cameraController,
                             const std::shared_ptr<Metrics::IMetricsService>& metricsService,
                             const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorsExplorerModel>& interiorExplorerModel,
                             const std::shared_ptr<AppModes::SdkModel::IAppModeModel>& appModeModel,
                             const std::shared_ptr<Eegeo::UI::NativeAlerts::IAlertBoxFactory>& alertBoxFactory);

                ~CompassModel();

                bool GetGpsModeActive() const;

                GpsMode::Values GetGpsMode() const;

                void DisableGpsMode();

                void TryUpdateToNavigationServiceGpsMode(Eegeo::Location::NavigationService::GpsMode value);

                float GetHeadingRadians() const;

                float GetHeadingDegrees() const;

                void CycleToNextGpsMode();

                void InsertGpsModeChangedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveGpsModeChangedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void InsertGpsModeUnauthorizedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void RemoveGpsModeUnauthorizedCallback(Eegeo::Helpers::ICallback0& callback);

            private:
                void SetGpsMode(GpsMode::Values value);
                
                void OnAppModeChanged();
                
                void OnInteriorFloorChanged();
                
                void OnFailedToGetLocation();
                
                bool NeedsToExitInterior(GpsMode::Values gpsMode);
            };
        }
    }
}
