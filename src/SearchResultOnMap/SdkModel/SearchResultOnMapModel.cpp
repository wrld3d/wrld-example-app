// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultOnMapItemModel.h"
#include "SearchResultOnMapModel.h"
#include "IWorldPinsService.h"
#include "ISearchResultOnMapFactory.h"
#include "ISearchResultRepository.h"
#include "SearchResultModel.h"
#include "ISearchResultOnMapIconCategoryMapper.h"
#include "WorldPinFocusData.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace SdkModel
        {
            SearchResultOnMapModel::SearchResultOnMapModel(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                    View::ISearchResultOnMapFactory& searchResultOnMapFactory,
                    View::ISearchResultOnMapIconCategoryMapper& searchResultOnMapIconCategoryMapper,
                    Search::SdkModel::ISearchResultRepository& searchResultRepository)
                : m_searchResultRepository(searchResultRepository)
                , m_searchResultOnMapIconCategoryMapper(searchResultOnMapIconCategoryMapper)
                , m_searchResultOnMapFactory(searchResultOnMapFactory)
                , m_worldPinsService(worldPinsService)
                , m_pSearchResultAddedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<SearchResultOnMapModel, Search::SdkModel::SearchResultModel*>))(this, &SearchResultOnMapModel::AddSearchResult))
                , m_pSearchResultRemovedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<SearchResultOnMapModel, Search::SdkModel::SearchResultModel*>))(this, &SearchResultOnMapModel::RemoveSearchResult))
            {
                m_searchResultRepository.InsertItemAddedCallback(*m_pSearchResultAddedCallback);
                m_searchResultRepository.InsertItemRemovedCallback(*m_pSearchResultRemovedCallback);

                for(size_t i = 0; i < m_searchResultRepository.GetItemCount(); ++ i)
                {
                    Search::SdkModel::SearchResultModel* pModel = m_searchResultRepository.GetItemAtIndex(i);
                    AddSearchResult(pModel);
                }
            }

            SearchResultOnMapModel::~SearchResultOnMapModel()
            {
                m_searchResultRepository.RemoveItemAddedCallback(*m_pSearchResultAddedCallback);
                m_searchResultRepository.RemoveItemRemovedCallback(*m_pSearchResultRemovedCallback);

                Eegeo_DELETE m_pSearchResultAddedCallback;
                Eegeo_DELETE m_pSearchResultRemovedCallback;

                while(m_searchResultsToPinModel.size())
                {
                    mapIt it = m_searchResultsToPinModel.begin();
                    Search::SdkModel::SearchResultModel* pSearchResultModel = it->first;
                    RemoveSearchResult(pSearchResultModel);
                }
            }

            void SearchResultOnMapModel::AddSearchResult(Search::SdkModel::SearchResultModel*& pSearchResultModel)
            {
                mapIt it = m_searchResultsToPinModel.find(pSearchResultModel);
                Eegeo_ASSERT(it == m_searchResultsToPinModel.end(), "Trying to add a world pin for a search result, but pin has already been added.");

                View::SearchResultOnMapItemModel* pSearchResultOnMapItemModel = m_searchResultOnMapFactory.CreateSearchResultOnMapItemModel(*pSearchResultModel);

                const int pinIconIndex = m_searchResultOnMapIconCategoryMapper.GetIconIndexFromSearchResult(*pSearchResultModel);

                WorldPins::SdkModel::WorldPinFocusData worldPinFocusData(pSearchResultModel->GetTitle(), pSearchResultModel->GetAddress());

                ExampleApp::WorldPins::SdkModel::WorldPinItemModel *pinItemModel = m_worldPinsService.AddPin(pSearchResultOnMapItemModel,
                        worldPinFocusData,
                        pSearchResultModel->GetLocation(),
                        pinIconIndex);

                m_searchResultsToPinModel.insert(std::make_pair(pSearchResultModel, pinItemModel));
            }

            void SearchResultOnMapModel::RemoveSearchResult(Search::SdkModel::SearchResultModel*& pSearchResultModel)
            {
                mapIt it = m_searchResultsToPinModel.find(pSearchResultModel);
                Eegeo_ASSERT(it != m_searchResultsToPinModel.end(), "Trying to remove the world pin for a search result, but no pin exists for result.");

                ExampleApp::WorldPins::SdkModel::WorldPinItemModel* pinItemModel = it->second;
                m_worldPinsService.RemovePin(pinItemModel);
                m_searchResultsToPinModel.erase(it);
            }

            SearchResultOnMapModel::mapIt SearchResultOnMapModel::begin()
            {
                return m_searchResultsToPinModel.begin();
            }

            SearchResultOnMapModel::mapIt SearchResultOnMapModel::end()
            {
                return m_searchResultsToPinModel.end();
            }
        }
    }
}
