// Copyright Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IConnectivityService.h"
#include "RestrictedBuildingInfo.h"
#include "IRestrictedBuildingService.h"
#include "NativeUIFactories.h"
#include "Location.h"

namespace ExampleApp
{
    namespace WifiInfo
    {
        class RestrictedBuildingService:public IRestrictedBuildingService
        {
        public:
            
            RestrictedBuildingService(const std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*>&restrictedBuildingsInfo,
                                      Eegeo::Web::IConnectivityService& connectivityService,
                                      Eegeo::UI::NativeUIFactories& nativeUIFactories,
                                      Eegeo::Location::NavigationService& navigationService);
            ~RestrictedBuildingService();

            bool IsRestrictedBuilding(std::string interior_id);
            bool CanAccessBuildingWithCurrentNetwork(std::string interior_id);
            void ShowAlertMessage();
            void HandleAlertBoxDismissed();
            
        private:
            
            bool m_isRestrictedBuildingAlertShown;
            Eegeo::Web::IConnectivityService& m_connectivityService;
            const std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*>&m_restrictedBuildingsInfo;
            Eegeo::UI::NativeUIFactories& m_nativeUIFactories;
            Eegeo::UI::NativeAlerts::ISingleOptionAlertBoxDismissedHandler* m_pAlertBoxDismissedHandler;
            Eegeo::Location::NavigationService& m_navigationService;
        };
    }
}
