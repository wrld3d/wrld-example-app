// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultItemModel.h"
#include "SearchResultMenuModel.h"
#include "IMenuOptionsModel.h"
#include "ISearchResultRepository.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        SearchResultMenuModel::SearchResultMenuModel(Menu::IMenuOptionsModel& menuOptions,
                                                     Search::ISearchResultRepository& searchResultRepository,
                                                     CameraTransitions::ICameraTransitionController& cameraTransitionController,
                                                     OpenableControlViewModel::IOpenableControlViewModel& searchResultsMenuOpenableViewModel)
        : m_searchResultRepository(searchResultRepository)
        , m_menuOptions(menuOptions)
        , m_pSearchResultAddedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<SearchResultMenuModel, Search::SearchResultModel*>))(this, &SearchResultMenuModel::AddSearchResult))
        , m_pSearchResultRemovedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<SearchResultMenuModel, Search::SearchResultModel*>))(this, &SearchResultMenuModel::RemoveSearchResult))
        , m_cameraTransitionController(cameraTransitionController)
        , m_searchResultsMenuOpenableViewModel(searchResultsMenuOpenableViewModel)
        {
            m_searchResultRepository.InsertItemAddedCallback(*m_pSearchResultAddedCallback);
            m_searchResultRepository.InsertItemRemovedCallback(*m_pSearchResultRemovedCallback);
            
            for(size_t i = 0; i < m_searchResultRepository.GetItemCount(); ++ i)
            {
                Search::SearchResultModel* pModel = m_searchResultRepository.GetItemAtIndex(i);
                AddSearchResult(pModel);
            }
        }
        
        SearchResultMenuModel::~SearchResultMenuModel()
        {
            m_searchResultRepository.RemoveItemAddedCallback(*m_pSearchResultAddedCallback);
            m_searchResultRepository.RemoveItemRemovedCallback(*m_pSearchResultRemovedCallback);
            
            Eegeo_DELETE m_pSearchResultAddedCallback;
            Eegeo_DELETE m_pSearchResultRemovedCallback;
        }
        
        void SearchResultMenuModel::AddSearchResult(Search::SearchResultModel*& pModel)
        {
            m_menuOptions.AddItem(pModel->GetIdentifier(),
                                  pModel->GetTitle(), pModel->GetAddress(), pModel->GetCategory(),
                                  Eegeo_NEW(SearchResultItemModel)(pModel->GetTitle(),
                                                                   *pModel,
                                                                   m_cameraTransitionController,
                                                                   m_searchResultsMenuOpenableViewModel));
        }
        
        void SearchResultMenuModel::RemoveSearchResult(Search::SearchResultModel*& pModel)
        {
            m_menuOptions.RemoveItem(pModel->GetIdentifier());
        }
    }
}
