// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "Types.h"
#include "IConnectivityService.h"
#include "InteriorSelectionModel.h"
#include "InteriorsExplorerModel.h"
#include "IRestrictedBuildingService.h"


namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorExplorerConnectionChangedObserver
            {
            public:

                void OnWifiDisconnected();
                void OnWifiInfoChange(std::string wifiSSID);
                ~InteriorExplorerConnectionChangedObserver();
                void HandleConnectionChanged(const bool &connected);
                InteriorExplorerConnectionChangedObserver(Eegeo::Web::IConnectivityService& connectivityService,
                                                          Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                          InteriorsExplorerModel& interiorExplorerModel,
                                                          ExampleApp::WifiInfo::IRestrictedBuildingService& restrictedBuildingInformationService);

            
            private:
                bool m_connectivityStatus;
                InteriorsExplorerModel& m_interiorExplorerModel;
                Eegeo::Web::IConnectivityService& m_connectivityService;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                ExampleApp::WifiInfo::IRestrictedBuildingService& m_restrictedBuildingInformationService;
                Eegeo::Helpers::TCallback1<InteriorExplorerConnectionChangedObserver, const bool&> m_connectionChangedCallback;



            
            };
        
        }
    }
}
