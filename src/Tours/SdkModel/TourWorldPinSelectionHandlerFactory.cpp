// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourWorldPinSelectionHandlerFactory.h"
#include "TourWorldPinSelectionHandler.h"
#include "IAppModeModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            TourWorldPinSelectionHandlerFactory::TourWorldPinSelectionHandlerFactory(ITourService& tourService,
                                                                                     Search::SdkModel::ISearchRefreshService& searchRefreshService,
                                                                                     AppModes::SdkModel::IAppModeModel& appModeModel)
            : m_tourService(tourService)
            , m_searchRefreshService(searchRefreshService)
            , m_appModeModel(appModeModel)
            {
                
            }
            
            ExampleApp::WorldPins::SdkModel::IWorldPinSelectionHandler* TourWorldPinSelectionHandlerFactory::CreateSelectionHandler(TourModel& model)
            {
                return Eegeo_NEW(TourWorldPinSelectionHandler)(model,
                                                               m_tourService,
                                                               m_searchRefreshService,
                                                               m_appModeModel);
            }
        };
    }
}
