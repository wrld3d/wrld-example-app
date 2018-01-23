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
            ,m_interiorExplorerModel(interiorExplorerModel)
            ,m_restrictedBuildingInformationService(restrictedBuildingInformationService)
            {
            }

            InteriorExplorerConnectionChangedObserver::~InteriorExplorerConnectionChangedObserver()
            {
            }

            void InteriorExplorerConnectionChangedObserver::OnWifiDisconnected()
            {
                if (m_interiorSelectionModel.IsInteriorSelected() && !AuthorisedForCurrentInterior())
                {
                    m_interiorExplorerModel.Exit();
                    m_restrictedBuildingInformationService.ShowAlertMessage();
                }
            }

            bool InteriorExplorerConnectionChangedObserver::AuthorisedForCurrentInterior()
            {
                std::string interior_id = m_interiorSelectionModel.GetSelectedInteriorId().Value();

                bool buildingRequiresValidAuthorisation = m_restrictedBuildingInformationService.IsRestrictedBuilding(interior_id);
                bool buildingHasValidAuthorisation = m_connectivityService.HasConnectivity() && m_restrictedBuildingInformationService.CanAccessBuildingWithCurrentNetwork(interior_id);

                return !buildingRequiresValidAuthorisation || buildingHasValidAuthorisation;
            }
        }
    }
}
