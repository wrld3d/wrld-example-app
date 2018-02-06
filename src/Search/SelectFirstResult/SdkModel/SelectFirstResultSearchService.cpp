// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SelectFirstResultSearchService.h"
#include "SearchQueryPerformer.h"
#include "IMenuOption.h"
#include "ISearchResultRepository.h"
#include "IMenuModel.h"
#include "SearchResultItemModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SelectFirstResult
        {
            namespace SdkModel
            {
                SelectFirstResultSearchService::SelectFirstResultSearchService(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                     Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                     ExampleAppMessaging::TMessageBus& messageBus)
                : m_searchQueryPerformer(searchQueryPerformer)
                , m_searchResultRepository(searchResultRepository)
                , m_searchResultAddedCallback(this, &SelectFirstResultSearchService::OnSearchResultAdded)
                , m_didTransition(true)
                , m_messageBus(messageBus)
                {
                    m_searchResultRepository.InsertItemAddedCallback(m_searchResultAddedCallback);
                }
                
                SelectFirstResultSearchService::~SelectFirstResultSearchService()
                {
                    m_searchResultRepository.RemoveItemAddedCallback(m_searchResultAddedCallback);
                }
                
                void SelectFirstResultSearchService::HandleSearch(std::string& queryString, const std::string& interiorId)
                {
                    m_searchQueryPerformer.RemoveSearchQueryResults();
                    m_searchQueryPerformer.PerformSearchQuery(queryString.c_str(), false, true, interiorId);
                    
                    m_didTransition = false;
                }
                
                void SelectFirstResultSearchService::OnSearchResultAdded(Search::SdkModel::SearchResultModel*& pSearchResultModel)
                {
                    if(!m_didTransition)
                    {
                        m_didTransition = true;

                        m_messageBus.Publish(SearchResultSection::SearchResultSectionItemSelectedMessage(pSearchResultModel->GetLocation().ToECEF(),
                                                                                                         pSearchResultModel->IsInterior(),
                                                                                                         pSearchResultModel->GetBuildingId(),
                                                                                                         pSearchResultModel->GetFloor(),
                                                                                                         0,
                                                                                                         pSearchResultModel->GetIdentifier()));
                    }
                }
            }
        }
    }
}


