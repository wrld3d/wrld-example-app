// Copyright eeGeo Ltd (2012-2015), All Rights Reserved



#include "InteriorExplorerConnectionChangedObserver.h"


namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorExplorerConnectionChangedObserver::InteriorExplorerConnectionChangedObserver(Eegeo::Web::IConnectivityService& connectivityService,
                                                                                                 Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                                                 InteriorsExplorerModel& interiorExplorerModel,
                                                                                                 ExampleApp::WifiInfo::IRestrictedBuildingService& restrictedBuildingInformationService)
            :m_connectivityService(connectivityService)
            ,m_interiorSelectionModel(interiorSelectionModel)
            ,m_connectionChangedCallback(this, &InteriorExplorerConnectionChangedObserver::HandleConnectionChanged)
            ,m_interiorExplorerModel(interiorExplorerModel)
            ,m_restrictedBuildingInformationService(restrictedBuildingInformationService)
            {
                
                m_connectivityService.RegisterConnectivityChangedCallback(m_connectionChangedCallback);
                m_connectivityStatus = m_connectivityService.HasConnectivity();
            
            }
            InteriorExplorerConnectionChangedObserver::~InteriorExplorerConnectionChangedObserver()
            {
                m_connectivityService.UnregisterConnectivityChangedCallback(m_connectionChangedCallback);
            }
            void InteriorExplorerConnectionChangedObserver::OnWifiInfoChange(std::string wifiSSID)
            {
                if (m_interiorSelectionModel.IsInteriorSelected() == true)
                {
                    
                    if(m_restrictedBuildingInformationService.CanAccessBuildingWithCurrentNetwork(m_interiorSelectionModel.GetSelectedInteriorId().Value()) == false)
                    {
                        m_interiorExplorerModel.Exit();
                        m_restrictedBuildingInformationService.ShowAlertMessage();
                    }
                }
            
            }
            void InteriorExplorerConnectionChangedObserver::OnWifiDisconnected()
            {
                if (m_interiorSelectionModel.IsInteriorSelected() && !m_restrictedBuildingInformationService.CanAccessBuildingWithCurrentNetwork(m_interiorSelectionModel.GetSelectedInteriorId().Value()))
                {
                    m_interiorExplorerModel.Exit();
                    m_restrictedBuildingInformationService.ShowAlertMessage();
                }

            }
            void InteriorExplorerConnectionChangedObserver::HandleConnectionChanged(const bool &connected)
            {
                
                if ((connected != m_connectivityStatus && !connected) || m_connectivityService.GetConnectivityType() !=  Eegeo::Web::Wifi)
                {
                    OnWifiDisconnected();
                    return;
                }
                //Currently Android implementation is not provided in ConnectivityService. So in Android will be using custom SSID information fetch. Once SDK
                //updated to reflect android will update here and will remove local implementation
                std::string ssid = m_connectivityService.GetSSIDForCurrentWifi();
                                
                if(!ssid.empty())
                {
                	// Removing the double quotes from start and end.
                	if (ssid.front() == '"'  && ssid.back() == '"')
                	 {
						  ssid.erase( 0, 1 );
						  ssid.erase( ssid.size() - 1 );
                	 }
                    OnWifiInfoChange(ssid);
                }
                else
                {
                    OnWifiDisconnected();
                    return;
                }
                
                m_connectivityStatus = connected;
            
            }
        }
    }
}
