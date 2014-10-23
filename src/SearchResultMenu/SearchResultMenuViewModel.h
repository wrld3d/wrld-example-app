// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "MenuViewModel.h"
#include "ISearchResultMenuViewModel.h"
#include "ICallback.h"
#include "Reaction.h"
#include "Search.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        class SearchResultMenuViewModel : public ISearchResultMenuViewModel, public Menu::MenuViewModel, private Eegeo::NonCopyable
        {
        private:
            Menu::IMenuModel& m_menuModel;
            float m_realOnScreenState;
            Eegeo::Helpers::ICallback1<Menu::MenuItemModel>* m_pMenuContentsChangedCallback;
            const Search::ISearchQueryPerformer& m_searchQueryPerformer;
            Search::ISearchService& m_searchService;
            Eegeo::Helpers::ICallback1<const Search::SearchQuery &>* m_pSearchQueryPerformedCallback;
            Eegeo::Helpers::ICallback0* m_pModalReactorOpenControlReleasedCallback;
            Reaction::IReactionControllerModel& m_reactionControllerModel;
            
            void HandleMenuContentsChanged(Menu::MenuItemModel& item);
            
            bool CanShowOnScreen() const;
            
            void HandleSearchQueryPerformed(const Search::SearchQuery& query);
            
            void UpdateOnScreenState();
            
            void HandleReactorOpenControlReleased();
            
        public:
            SearchResultMenuViewModel(Menu::IMenuModel& menuModel,
                                      bool isInitiallyOnScreen,
                                      Eegeo::Helpers::TIdentity identity,
                                      Reaction::IReactionControllerModel& reactionControllerModel,
                                      const Search::ISearchQueryPerformer& searchQueryPerformer,
                                      Search::ISearchService& searchService);
            
            ~SearchResultMenuViewModel();
            
            bool CanInteract() const;
            
            void AddToScreen();
            
            void RemoveFromScreen();
            
            void UpdateOnScreenState(float onScreenState);
        };
    }
}
