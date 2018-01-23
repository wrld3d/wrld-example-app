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
                InteriorExplorerConnectionChangedObserver(Eegeo::Web::IConnectivityService& connectivityService,
                                                          Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                          InteriorsExplorerModel& interiorExplorerModel,
                                                          ExampleApp::WifiInfo::IRestrictedBuildingService& restrictedBuildingInformationService);
                ~InteriorExplorerConnectionChangedObserver();

                void OnWifiDisconnected();
                bool AuthorisedForCurrentInterior();
            
            private:
                Eegeo::Web::IConnectivityService& m_connectivityService;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                InteriorsExplorerModel& m_interiorExplorerModel;
                ExampleApp::WifiInfo::IRestrictedBuildingService& m_restrictedBuildingInformationService;
            };
        }
    }
}
