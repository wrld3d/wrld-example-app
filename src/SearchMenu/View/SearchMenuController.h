// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuController.h"

#include "TagSearch.h"
#include "Modality.h"
#include "SearchMenu.h"
#include "SearchMenuOptions.h"
#include "IModalityController.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchMenuController : public Menu::View::MenuController
            {
            private:
                const std::shared_ptr<ISearchMenuView> m_searchMenuView;
                const std::shared_ptr<Menu::View::IMenuSectionViewModel> m_searchSectionViewModel;
                const std::shared_ptr<TagSearch::View::ITagSearchRepository> m_tagSearchRepository;
                const std::shared_ptr<Modality::View::IModalBackgroundView> m_modalBackgroundView;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                bool m_appModeAllowsOpen;
                
                Eegeo::Helpers::TCallback1<SearchMenuController, Menu::View::MenuItemModel> m_onSearchItemAddedCallback;
                Eegeo::Helpers::TCallback1<SearchMenuController, Menu::View::MenuItemModel> m_onSearchItemRemovedCallback;
                Eegeo::Helpers::TCallback2<SearchMenuController, OpenableControl::View::IOpenableControlViewModel&, float> m_onOpenStateChangedCallback;
                Eegeo::Helpers::TCallback1<SearchMenuController, const Search::SearchQueryPerformedMessage&> m_performedQueryHandler;
                Eegeo::Helpers::TCallback1<SearchMenuController, const Search::SearchQueryResponseReceivedMessage&> m_receivedQueryResponseHandler;
                Eegeo::Helpers::TCallback1<SearchMenuController, const std::string&> m_onSearchCallback;
                Eegeo::Helpers::TCallback0<SearchMenuController> m_onSearchClearedCallback;
                Eegeo::Helpers::TCallback1<SearchMenuController, int> m_onSearchItemSelectedCallback;
                Eegeo::Helpers::TCallback1<SearchMenuController, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                Eegeo::Helpers::TCallback0<SearchMenuController> m_onModalBackgroundTappedCallback;
                
                void OnSearchItemAdded(Menu::View::MenuItemModel& item);
                
                void OnSearchItemRemoved(Menu::View::MenuItemModel& item);
                
                void OnOpenStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);
                
                void OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message);
                
                void OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message);
                
                void OnSearch(const std::string& searchQuery);
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                
                bool TryDrag();
                
                void OnViewClicked();
                
                void OnSearchCleared();
                
                void OnSearchItemSelected(int& index);
                
                void OnModalBackgroundTapped();
                
            protected:
                
                virtual void RefreshPresentation();
                bool IsFullyOpen() const;
                void UpdateOpenState();
                
            public:
                SearchMenuController(const std::shared_ptr<SearchMenuModel>& model,
                                     const std::shared_ptr<SearchMenuViewModel>& viewModel,
                                     const std::shared_ptr<Menu::View::IMenuView>& view,
                                     const std::shared_ptr<ISearchMenuView>& searchMenuView,
                                     const std::shared_ptr<SearchMenuSectionViewModel>& searchSectionViewModel,
                                     const std::shared_ptr<TagSearch::View::ITagSearchRepository>& tagSearchRepository,
                                     const std::shared_ptr<Modality::View::IModalBackgroundView>& modalBackgroundView,
                                     const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                virtual ~SearchMenuController();
            };
        }
    }
}