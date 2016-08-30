// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <set>
#include "Types.h"
#include "ISearchResultOnMapModel.h"
#include "SearchResultOnMap.h"
#include "CategorySearch.h"
#include "Search.h"
#include "WorldPins.h"
#include "MyPins.h"
#include "ICallback.h"

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
                
                Eegeo::Helpers::TCallback1<SearchResultOnMapModel, Search::SdkModel::SearchResultModel*> m_searchResultAddedCallback;
                Eegeo::Helpers::TCallback1<SearchResultOnMapModel, Search::SdkModel::SearchResultModel*> m_searchResultRemovedCallback;
                Eegeo::Helpers::TCallback1<SearchResultOnMapModel, Search::SdkModel::SearchResultModel> m_searchResultPinnedCallback;
                Eegeo::Helpers::TCallback1<SearchResultOnMapModel, Search::SdkModel::SearchResultModel> m_searchResultUnpinnedCallback;
                
                const std::shared_ptr<Search::SdkModel::MyPins::ISearchResultMyPinsService> m_searchResultOnMapMyPinsService;
                const std::shared_ptr<MyPins::SdkModel::IMyPinsService> m_myPinsService;
                const std::shared_ptr<Search::SdkModel::ISearchResultRepository> m_searchResultRepository;
                const std::shared_ptr<CategorySearch::ISearchResultIconCategoryMapper> m_searchResultIconCategoryMapper;
                const std::shared_ptr<View::ISearchResultOnMapFactory> m_searchResultOnMapFactory;
                const std::shared_ptr<WorldPins::SdkModel::IWorldPinsService> m_worldPinsService;

            public:
                SearchResultOnMapModel(const std::shared_ptr<WorldPins::SdkModel::IWorldPinsService>& worldPinsService,
                                       const std::shared_ptr<MyPins::SdkModel::IMyPinsService>& myPinsService,
                                       const std::shared_ptr<View::ISearchResultOnMapFactory>& searchResultOnMapFactory,
                                       const std::shared_ptr<Search::SdkModel::MyPins::ISearchResultMyPinsService>& searchResultOnMapMyPinsService,
                                       const std::shared_ptr<CategorySearch::ISearchResultIconCategoryMapper>& searchResultIconCategoryMapper,
                                       const std::shared_ptr<Search::SdkModel::ISearchResultRepository>& searchResultRepository);

                ~SearchResultOnMapModel();

                mapIt begin();

                mapIt end();

            private:
                void AddSearchResultOnMap(Search::SdkModel::SearchResultModel& searchResultModel);
                
                void RemoveSearchResultOnMap(Search::SdkModel::SearchResultModel& searchResultModel);
                
                void HandleAddedSearchResult(Search::SdkModel::SearchResultModel*& pSearchResultModel);

                void HandleRemovedSearchResult(Search::SdkModel::SearchResultModel*& pSearchResultModel);
                
                void HandleSearchResultPinned(Search::SdkModel::SearchResultModel& searchResultModel);
                
                void HandleSearchResultUnpinned(Search::SdkModel::SearchResultModel& searchResultModel);
            };
        }
    }
}
