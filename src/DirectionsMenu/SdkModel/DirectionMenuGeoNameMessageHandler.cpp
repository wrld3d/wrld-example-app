// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionMenuGeoNameMessageHandler.h"
#include "SearchQuery.h"
#include "DirectionMenuGeoNamesResponseReceivedMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            DirectionMenuGeoNameMessageHandler::DirectionMenuGeoNameMessageHandler(ExampleApp::Search::GeoNames::SdkModel::GeoNamesSearchService & geoNamesService, ExampleAppMessaging::TMessageBus& messageBus)
            
            :m_handleFindDirectionMessageBinding(this, &DirectionMenuGeoNameMessageHandler::OnFindDirectionMessage)
            , m_geoNamesService(geoNamesService)
            , m_searchQueryResponseCallback(this, &DirectionMenuGeoNameMessageHandler::OnSearchResponseRecieved)
            , m_messageBus(messageBus)
            {
                m_messageBus.SubscribeNative(m_handleFindDirectionMessageBinding);
                m_geoNamesService.InsertOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
            }
            DirectionMenuGeoNameMessageHandler::~DirectionMenuGeoNameMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handleFindDirectionMessageBinding);
                m_geoNamesService.RemoveOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
                
                
            }
            void DirectionMenuGeoNameMessageHandler::OnFindDirectionMessage(const DirectionsMenu::DirectionMenuGetGeoNamesMessage& message)
            {                
                bool isTag = false;
                bool tryInteriorSearch = false;
                Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude(0.0f,0.0f,0.0f);
                float radius = 200.0f;
                Search::SdkModel::SearchQuery searchQuery(message.SearchQuery(), isTag, tryInteriorSearch, location, radius);
                m_geoNamesService.PerformLocationQuerySearch(searchQuery);
                
            }

            void DirectionMenuGeoNameMessageHandler::OnSearchResponseRecieved(const Search::SdkModel::SearchQuery& query,
                                                                 const std::vector<Search::SdkModel::SearchResultModel>& results)
            {
                Eegeo_TTY("Response Received");
                
                m_messageBus.Publish(DirectionsMenu::DirectionMenuGeoNamesResponseReceivedMessage(results));
                
                
//                std::vector<Search::SdkModel::SearchResultModel> filtered;
//                filtered.reserve(results.size());
//                
//                for (std::vector<Search::SdkModel::SearchResultModel>::const_iterator it = results.begin();
//                     it != results.end();
//                     it++)
//                {
//                    const Search::SdkModel::SearchResultModel& searchResult = *it;
//                    filtered.push_back(searchResult);
//                }
//                
//                m_combinedResults.insert(m_combinedResults.end(), filtered.begin(), filtered.end());
//                
//                if( --m_pendingResultsLeft <= 0)
//                {
//                    m_hasActiveQuery = false;
//                    m_pendingResultsLeft = 0;
//                    ExecutQueryResponseReceivedCallbacks(query, m_combinedResults);
//                    m_combinedResults.clear();
//                }
            }

        }
    }
}