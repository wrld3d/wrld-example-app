// Copyright Ltd (2012-2015), All Rights Reserved


#include "RestrictedBuildingService.h"
#include "IAlertBoxFactory.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "NavigationService.h"

namespace ExampleApp
{
    namespace WifiInfo
    {

        RestrictedBuildingService::RestrictedBuildingService(const std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*>&restrictedBuildingsInfo,
                                                             Eegeo::Web::IConnectivityService& connectivityService,
                                                             Eegeo::UI::NativeUIFactories& nativeUIFactories,
                                                             Eegeo::Location::NavigationService& navigationService)
        : m_restrictedBuildingsInfo(restrictedBuildingsInfo)
        , m_connectivityService(connectivityService)
        , m_nativeUIFactories(nativeUIFactories)
        , m_pAlertBoxDismissedHandler(NULL)
        , m_isRestrictedBuildingAlertShown(false)
        , m_navigationService(navigationService)
        {
             m_pAlertBoxDismissedHandler = Eegeo_NEW(Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<RestrictedBuildingService>(this, &RestrictedBuildingService::HandleAlertBoxDismissed));
        }
   
         RestrictedBuildingService::~RestrictedBuildingService()
        {
        
        }

        bool RestrictedBuildingService::IsRestrictedBuilding(std::string interior_id)
        {
            for(std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*>::const_iterator it = m_restrictedBuildingsInfo.begin(); it != m_restrictedBuildingsInfo.end(); ++it)
            {
                if ((*it)->InteriorID().compare(interior_id) == 0)
                {
                    return true;
                }
            }
            return false;
        }

        bool RestrictedBuildingService::CanAccessBuildingWithCurrentNetwork(std::string interior_id)
        {
            
            ExampleApp::ApplicationConfig::RestrictedBuildingInfo *respectiveBuilding = NULL;
            for(std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*>::const_iterator it = m_restrictedBuildingsInfo.begin(); it != m_restrictedBuildingsInfo.end(); ++it)
            {
                
                if ((*it)->InteriorID().compare(interior_id) == 0)
                {
                    respectiveBuilding = *it;
                    break;
                    
                }
            }
            
            if (respectiveBuilding == NULL)
            {
                return true;
            }
            else
            {
                //Currently Android implementation is not provided in ConnectivityService. So in Android will be using custom SSID information fetch. Once SDK
                //updated to reflect android will update here and will remove local implementation
                
                std::string ssid = m_connectivityService.GetSSIDForCurrentWifi();
                
                // Removing the double quotes from start and end.
                if (ssid.front() == '"'  && ssid.back() == '"')
                {
                	ssid.erase( 0, 1 );
                	ssid.erase( ssid.size() - 1 );
                }

                for(std::vector<std::string>::const_iterator it = respectiveBuilding->AllowedWifiIDs().begin(); it != respectiveBuilding->AllowedWifiIDs().end(); ++it)
                {
                    
                    if ((*it).compare(ssid) == 0)
                    {
                        return true;
                        break;
                        
                    }
                }
                return false;
                
            }

            return true;
        }
        
        void RestrictedBuildingService::ShowAlertMessage()
        {
            if(!m_isRestrictedBuildingAlertShown)
            {
            	m_nativeUIFactories.AlertBoxFactory().CreateSingleOptionAlertBox("Indoor Map Not Available", "Sorry, that indoor map cannot be explored over your current network.", *m_pAlertBoxDismissedHandler);
                
                m_isRestrictedBuildingAlertShown = true;
                
                m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsModeOff);
            }
        }
        
        void RestrictedBuildingService::HandleAlertBoxDismissed()
        {
            m_isRestrictedBuildingAlertShown = false;
        }
    }
}
