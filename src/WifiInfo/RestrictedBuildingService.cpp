// Copyright Ltd (2012-2015), All Rights Reserved


#include "RestrictedBuildingService.h"
#include "IAlertBoxFactory.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"

namespace ExampleApp
{
    namespace WifiInfo
    {

        RestrictedBuildingService::RestrictedBuildingService(const std::vector<ExampleApp::ApplicationConfig::RestrictedBuildingInfo*>&restrictedBuildingsInfo,
                                                             Eegeo::Web::IConnectivityService& connectivityService,
                                                             Eegeo::UI::NativeUIFactories& nativeUIFactories)
        : m_restrictedBuildingsInfo(restrictedBuildingsInfo),m_connectivityService(connectivityService),m_nativeUIFactories(nativeUIFactories), m_pAlertBoxDismissedHandler(NULL)
        {
             m_pAlertBoxDismissedHandler = Eegeo_NEW(Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<RestrictedBuildingService>(this, &RestrictedBuildingService::HandleAlertBoxDismissed));
        }
   
         RestrictedBuildingService::~RestrictedBuildingService()
        {
        
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
            m_nativeUIFactories.AlertBoxFactory().CreateSingleOptionAlertBox("Indoor Map Not Available", "Sorry, that indoor map cannot be explored over your current WiFi network.", *m_pAlertBoxDismissedHandler);
        }
        
        void RestrictedBuildingService::HandleAlertBoxDismissed()
        {
        }

        
    }
}
