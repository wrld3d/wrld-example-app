// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include "Types.h"
#include "ISearchResultOnMapModel.h"
#include "SearchResultOnMap.h"
#include "Search.h"
#include "WorldPins.h"
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

                typedef std::map<Search::SdkModel::SearchResultModel*, ExampleApp::WorldPins::SdkModel::WorldPinItemModel*>::iterator mapIt;

            private:
                std::map<Search::SdkModel::SearchResultModel*, ExampleApp::WorldPins::SdkModel::WorldPinItemModel*> m_searchResultsToPinModel;

                Search::SdkModel::ISearchResultRepository& m_searchResultRepository;
                View::ISearchResultOnMapIconCategoryMapper& m_searchResultOnMapIconCategoryMapper;
                View::ISearchResultOnMapFactory& m_searchResultOnMapFactory;

                WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel*>* m_pSearchResultAddedCallback;
                Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel*>* m_pSearchResultRemovedCallback;

            public:
                SearchResultOnMapModel(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                       View::ISearchResultOnMapFactory& searchResultOnMapFactory,
                                       View::ISearchResultOnMapIconCategoryMapper& searchResultOnMapIconCategoryMapper,
                                       Search::SdkModel::ISearchResultRepository& searchResultRepository);

                ~SearchResultOnMapModel();

                mapIt begin();

                mapIt end();

            private:
                void AddSearchResult(Search::SdkModel::SearchResultModel*& pSearchResultModel);

                void RemoveSearchResult(Search::SdkModel::SearchResultModel*& pSearchResultModel);
            };
        }
    }
}
