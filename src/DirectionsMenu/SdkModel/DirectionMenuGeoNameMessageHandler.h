// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "FindDirectionQueryPerformer.h"
#include "DirectionMenuGetGeoNamesMessage.h"
#include "GeoNamesSearchService.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            class DirectionMenuGeoNameMessageHandler : private Eegeo::NonCopyable
            {
            private:
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                ExampleApp::Search::GeoNames::SdkModel::GeoNamesSearchService & m_geoNamesService;
                
                Eegeo::Helpers::TCallback1<DirectionMenuGeoNameMessageHandler, const DirectionsMenu::DirectionMenuGetGeoNamesMessage&> m_handleFindDirectionMessageBinding;
                
                Eegeo::Helpers::TCallback2<DirectionMenuGeoNameMessageHandler,
                const Search::SdkModel::SearchQuery&,
                const std::vector<Search::SdkModel::SearchResultModel>&> m_searchQueryResponseCallback;
                
                bool m_isStartLocationActive;
                
                void OnGetGeoNamesReceivedMessage(const DirectionsMenu::DirectionMenuGetGeoNamesMessage& message);
                
                void OnSearchResponseRecieved(const Search::SdkModel::SearchQuery& query,
                                              const std::vector<Search::SdkModel::SearchResultModel>& results);
                
            public:
                
                DirectionMenuGeoNameMessageHandler(ExampleApp::Search::GeoNames::SdkModel::GeoNamesSearchService & geoNamesService, ExampleAppMessaging::TMessageBus& messageBus);
                ~DirectionMenuGeoNameMessageHandler();
                
            };
        }
    }
}
