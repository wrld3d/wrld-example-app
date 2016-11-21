// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <set>
#include <vector>
#include "Types.h"
#include "ISearchResultOnMapModel.h"
#include "SearchResultOnMap.h"
#include "TagSearch.h"
#include "Search.h"
#include "WorldPins.h"
#include "MyPins.h"
#include "ICallback.h"
#include "SearchResultMeetingAvailabilityChanged.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace SdkModel
        {
            class SearchResultOnMapModel : public ISearchResultOnMapModel, private Eegeo::NonCopyable
            {
            public:

                typedef std::map<Search::SdkModel::SearchResultModel, ExampleApp::WorldPins::SdkModel::WorldPinItemModel*>::iterator mapIt;

            private:
                typedef std::set<Search::SdkModel::SearchResultModel>::iterator setIt;
                
                std::map<Search::SdkModel::SearchResultModel, ExampleApp::WorldPins::SdkModel::WorldPinItemModel*> m_searchResultsToPinModel;
                std::set<Search::SdkModel::SearchResultModel> m_activeSearchResults;
                std::set<Search::SdkModel::SearchResultModel> m_hiddenSearchResultsDueToMyPins;
                
                std::string m_currentSelectedId;
                
                Eegeo::Helpers::TCallback1<SearchResultOnMapModel, Search::SdkModel::SearchResultModel*> m_searchResultAddedCallback;
                Eegeo::Helpers::TCallback1<SearchResultOnMapModel, Search::SdkModel::SearchResultModel*> m_searchResultRemovedCallback;
                Eegeo::Helpers::TCallback1<SearchResultOnMapModel, Search::SdkModel::SearchResultModel> m_searchResultPinnedCallback;
                Eegeo::Helpers::TCallback1<SearchResultOnMapModel, Search::SdkModel::SearchResultModel> m_searchResultUnpinnedCallback;
                Eegeo::Helpers::TCallback2<SearchResultOnMapModel, const Search::SdkModel::SearchQuery&, const std::vector<Search::SdkModel::SearchResultModel>&> m_searchResultsCallback;
                
                Eegeo::Helpers::TCallback1<SearchResultOnMapModel, const SearchResultMeetingAvailabilityChanged&> m_availbilityChangedMessage;
                
                Eegeo::Helpers::TCallback1<SearchResultOnMapModel, const SearchResultSection::SearchResultSectionItemSelectedMessage&> m_searchResultSectionItemSelectedMessageHandler;
                
                
                Search::SdkModel::MyPins::ISearchResultMyPinsService& m_searchResultOnMapMyPinsService;
                MyPins::SdkModel::IMyPinsService& m_myPinsService;
                Search::SdkModel::ISearchResultRepository& m_searchResultRepository;
                Search::SdkModel::ISearchService& m_searchService;
                TagSearch::ISearchResultIconKeyMapper& m_searchResultIconKeyMapper;
                View::ISearchResultOnMapFactory& m_searchResultOnMapFactory;
                WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                ExampleAppMessaging::TMessageBus& m_messageBus;

            public:
                SearchResultOnMapModel(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                       MyPins::SdkModel::IMyPinsService& myPinsService,
                                       View::ISearchResultOnMapFactory& searchResultOnMapFactory,
                                       Search::SdkModel::MyPins::ISearchResultMyPinsService& searchResultOnMapMyPinsService,
                                       TagSearch::ISearchResultIconKeyMapper& searchResultIconKeyMapper,
                                       ExampleAppMessaging::TMessageBus& messageBus,
                                       Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                       Search::SdkModel::ISearchService& searchService);

                ~SearchResultOnMapModel();


            private:
                void AddSearchResultOnMap(Search::SdkModel::SearchResultModel& searchResultModel);
                
                void RemoveSearchResultOnMap(Search::SdkModel::SearchResultModel& searchResultModel);
                
                void HandleAddedSearchResult(Search::SdkModel::SearchResultModel*& pSearchResultModel);

                void HandleRemovedSearchResult(Search::SdkModel::SearchResultModel*& pSearchResultModel);
                
                void HandleSearchResultsReceived(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results);
                
                void HandleSearchResultPinned(Search::SdkModel::SearchResultModel& searchResultModel);
                
                void HandleSearchResultUnpinned(Search::SdkModel::SearchResultModel& searchResultModel);
                
                void OnSearchResultMeetingAvailbilityChanged(const SearchResultMeetingAvailabilityChanged& meetingAvailbilityChangedMessage);
                
                void OnSearchResultSectionItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& searchesultSectionItemSelectedMessage);
                
                const Search::SdkModel::SearchResultModel* GetSelectedSearchResultModelOrNull() const;
                
                void RefreshPinsForSelection();
            };
        }
    }
}
