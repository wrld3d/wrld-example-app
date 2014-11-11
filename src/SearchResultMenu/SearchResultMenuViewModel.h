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
        class SearchResultMenuViewModel : public ISearchResultMenuViewModel, public Menu::MenuViewModel
        {
        private:
            Menu::IMenuModel& m_menuModel;
            float m_realOnScreenState;
            Eegeo::Helpers::ICallback1<Menu::MenuItemModel>* m_pMenuContentsChangedCallback;
            Eegeo::Helpers::ICallback0* m_pModalReactorOpenControlReleasedCallback;
            Reaction::IReactionControllerModel& m_reactionControllerModel;
            bool m_hasSearchQuery;
            
            void HandleMenuContentsChanged(Menu::MenuItemModel& item);
            
            bool CanShowOnScreen() const;
            
            void UpdateOnScreenState();
            
            void HandleReactorOpenControlReleased();
            
        public:
            SearchResultMenuViewModel(Menu::IMenuModel& menuModel,
                                      bool isInitiallyOnScreen,
                                      Eegeo::Helpers::TIdentity identity,
                                      Reaction::IReactionControllerModel& reactionControllerModel);
            
            ~SearchResultMenuViewModel();
            
            bool CanInteract() const;
            
            void AddToScreen();
            
            void RemoveFromScreen();
            
            void SetHasSearchQuery(bool hasSearchQuery);

            void UpdateOnScreenState(float onScreenState);
        };
    }
}
