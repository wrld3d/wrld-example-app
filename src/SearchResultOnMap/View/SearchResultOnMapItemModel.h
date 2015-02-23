// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinSelectionHandler.h"
#include "Search.h"
#include "SearchResultPoi.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace View
        {
            class SearchResultOnMapItemModel : public WorldPins::SdkModel::IWorldPinSelectionHandler, private Eegeo::NonCopyable
            {
                Search::SdkModel::SearchResultModel m_searchResultModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

            public:
                SearchResultOnMapItemModel(const Search::SdkModel::SearchResultModel& searchResultModel,
                                           ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultOnMapItemModel();

                void SelectPin();
            };
        }
    }
}
