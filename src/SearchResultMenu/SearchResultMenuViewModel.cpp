// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultMenuViewModel.h"
#include "IMenuModel.h"
#include "ISearchQueryPerformer.h"
#include "ISearchService.h"
#include "IReactionControllerModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        SearchResultMenuViewModel::SearchResultMenuViewModel(Menu::IMenuModel& menuModel,
                                                             bool isInitiallyOnScreen,
                                                             Eegeo::Helpers::TIdentity identity,
                                                             Reaction::IReactionControllerModel& reactionControllerModel,
                                                             const Search::ISearchQueryPerformer& searchQueryPerformer,
                                                             Search::ISearchService& searchService)
        : Menu::MenuViewModel(isInitiallyOnScreen, identity, reactionControllerModel)
        , m_menuModel(menuModel)
        , m_realOnScreenState(isInitiallyOnScreen ? 1.f : 0.f)
        , m_pMenuContentsChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<SearchResultMenuViewModel, Menu::MenuItemModel>))(this, &SearchResultMenuViewModel::HandleMenuContentsChanged))
        , m_searchQueryPerformer(searchQueryPerformer)
        , m_searchService(searchService)
        , m_pSearchQueryPerformedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<SearchResultMenuViewModel, const Search::SearchQuery&>))(this, &SearchResultMenuViewModel::HandleSearchQueryPerformed))
        , m_pModalReactorOpenControlReleasedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback0<SearchResultMenuViewModel>))(this, &SearchResultMenuViewModel::HandleReactorOpenControlReleased))
        , m_reactionControllerModel(reactionControllerModel)
        {
            m_searchService.InsertOnPerformedQueryCallback(*m_pSearchQueryPerformedCallback);
            m_menuModel.InsertItemAddedCallback(*m_pMenuContentsChangedCallback);
            m_menuModel.InsertItemRemovedCallback(*m_pMenuContentsChangedCallback);
            m_reactionControllerModel.InsertOpenControlReleasedCallback(*m_pModalReactorOpenControlReleasedCallback);
        }
        
        SearchResultMenuViewModel::~SearchResultMenuViewModel()
        {
            m_reactionControllerModel.RemoveOpenControlReleasedCallback(*m_pModalReactorOpenControlReleasedCallback);
            m_menuModel.RemoveItemAddedCallback(*m_pMenuContentsChangedCallback);
            m_menuModel.RemoveItemRemovedCallback(*m_pMenuContentsChangedCallback);
            m_searchService.RemoveOnPerformedQueryCallback(*m_pSearchQueryPerformedCallback);
            Eegeo_DELETE m_pModalReactorOpenControlReleasedCallback;
            Eegeo_DELETE m_pMenuContentsChangedCallback;
            Eegeo_DELETE m_pSearchQueryPerformedCallback;
        }
        
        bool SearchResultMenuViewModel::CanShowOnScreen() const
        {
            if(!m_searchQueryPerformer.HasQuery())
            {
                return false;
            }
            
            if(m_reactionControllerModel.IsAnyOpenableOpen())
            {
                return m_reactionControllerModel.IsOpenableOpen(GetIdentity());
            }
            
            return true;
        }

        bool SearchResultMenuViewModel::CanInteract() const
        {
            return CanShowOnScreen() && m_menuModel.GetItemCount() > 0;
        }
        
        void SearchResultMenuViewModel::AddToScreen()
        {
            if(CanShowOnScreen())
            {
                if(Menu::MenuViewModel::IsFullyOffScreen())
                {
                    Menu::MenuViewModel::AddToScreen();
                }
            }
            m_realOnScreenState = 1.f;
        }
        
        void SearchResultMenuViewModel::RemoveFromScreen()
        {
            Menu::MenuViewModel::RemoveFromScreen();
            m_realOnScreenState = 0.f;
        }
        
        void SearchResultMenuViewModel::UpdateOnScreenState(float onScreenState)
        {
            m_realOnScreenState = onScreenState;
            UpdateOnScreenState();
        }
        
        void SearchResultMenuViewModel::HandleMenuContentsChanged(Menu::MenuItemModel& item)
        {
            UpdateOnScreenState();
        }
        
        void SearchResultMenuViewModel::UpdateOnScreenState()
        {
            if(CanShowOnScreen())
            {
                if(Menu::MenuViewModel::OnScreenState() != m_realOnScreenState)
                {
                    Menu::MenuViewModel::UpdateOnScreenState(m_realOnScreenState);
                }
            }
            else
            {
                Menu::MenuViewModel::UpdateOnScreenState(0.f);
            }
        }
        
        void SearchResultMenuViewModel::HandleSearchQueryPerformed(const Search::SearchQuery& query)
        {
            AddToScreen();
        }
        
        void SearchResultMenuViewModel::HandleReactorOpenControlReleased()
        {
            UpdateOnScreenState();
        }
    }
}
