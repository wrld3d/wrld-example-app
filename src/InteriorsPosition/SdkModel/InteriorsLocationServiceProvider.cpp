// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "InteriorsLocationServiceProvider.h"
#include "InteriorSelectionModel.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            InteriorsLocationServiceProvider::InteriorsLocationServiceProvider(InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                                               Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                               Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                                                               Eegeo::Location::ILocationService& defaultLocationService,
                                                                               TestLocationService& testLocationService)
            : m_currentLocationService(currentLocationService)
            //, m_defaultLocationService(defaultLocationService)
            //, m_testLocationService(testLocationService)
            , m_interiorsExplorerModel(interiorsExplorerModel)
            //, m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorExplorerEnteredCallback(this, &InteriorsLocationServiceProvider::OnInteriorExplorerEntered)
            , m_interiorExplorerExitCallback(this, &InteriorsLocationServiceProvider::OnInteriorExplorerExit)
            {
                m_interiorsExplorerModel.InsertInteriorExplorerEnteredCallback(m_interiorExplorerEnteredCallback);
                m_interiorsExplorerModel.InsertInteriorExplorerExitedCallback(m_interiorExplorerExitCallback);
            }
            
            InteriorsLocationServiceProvider::~InteriorsLocationServiceProvider()
            {
                m_interiorsExplorerModel.RemoveInteriorExplorerEnteredCallback(m_interiorExplorerEnteredCallback);
                m_interiorsExplorerModel.RemoveInteriorExplorerExitedCallback(m_interiorExplorerExitCallback);
            }
            
            void InteriorsLocationServiceProvider::OnInteriorExplorerEntered()
            {
                //const Eegeo::Resources::Interiors::InteriorId& interiorID = m_interiorSelectionModel.GetSelectedInteriorId();
                //if(interiorID == Eegeo::Resources::Interiors::InteriorId("westport_house"))
                //{
                //    Eegeo_TTY("using test location service");
                //    m_currentLocationService.SetLocationService(m_testLocationService);
                //}
            }
            
            void InteriorsLocationServiceProvider::OnInteriorExplorerExit()
            {
                //Eegeo_TTY("using default location service");
                //m_currentLocationService.SetLocationService(m_defaultLocationService);
            }
        }
    }
}