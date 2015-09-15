// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "IWorldPinSelectionHandler.h"
#include "BidirectionalBus.h"
#include "Types.h"
#include "Search.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            class TourWorldPinSelectionHandler : public ExampleApp::WorldPins::SdkModel::IWorldPinSelectionHandler, private Eegeo::NonCopyable
            {
                TourModel m_model;
                ITourService& m_tourService;
                Search::SdkModel::ISearchRefreshService& m_searchRefreshService;
                
            public:
                TourWorldPinSelectionHandler(TourModel& model,
                                             ITourService& tourService,
                                             Search::SdkModel::ISearchRefreshService& searchRefreshService);
                
                void SelectPin();
            };
        }
    }
}
