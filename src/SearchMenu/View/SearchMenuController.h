// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuController.h"

#include "TagSearch.h"
#include "Modality.h"
#include "SearchMenu.h"
#include "IModalityController.h"
#include "SearchQueryResultsRemovedMessage.h"
#include "SelectMenuItemMessage.h"
#include "OpenSearchMenuSectionMessage.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchMenuController : public Menu::View::MenuController
            {
            private:
                ISearchMenuView& m_searchMenuView;
                Menu::View::IMenuSectionViewModel& m_searchSectionViewModel;
                TagSearch::View::ITagSearchRepository& m_tagSearchRepository;
                Modality::View::IModalBackgroundView& m_modalBackgroundView;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                bool m_appModeAllowsOpen;
                Search::SdkModel::SearchQuery m_lastPerformedQuery;
                
                Eegeo::Helpers::TCallback1<SearchMenuController, Menu::View::MenuItemModel> m_onSearchItemAddedCallback;
                Eegeo::Helpers::TCallback1<SearchMenuController, Menu::View::MenuItemModel> m_onSearchItemRemovedCallback;
                Eegeo::Helpers::TCallback2<SearchMenuController, OpenableControl::View::IOpenableControlViewModel&, float> m_onOpenStateChangedCallback;
                Eegeo::Helpers::TCallback1<SearchMenuController, const Search::SearchQueryPerformedMessage&> m_performedQueryHandler;
                Eegeo::Helpers::TCallback1<SearchMenuController, const Search::SearchQueryResponseReceivedMessage&> m_receivedQueryResponseHandler;
                Eegeo::Helpers::TCallback1<SearchMenuController, const Search::SearchQueryResultsRemovedMessage&> m_receivedQueryResultsRemovedHandler;
                Eegeo::Helpers::TCallback1<SearchMenuController, const Automation::SelectMenuItemMessage&> m_menuItemSelectedHandler;
                Eegeo::Helpers::TCallback1<SearchMenuController, const std::string&> m_onSearchCallback;
                Eegeo::Helpers::TCallback0<SearchMenuController> m_onSearchClearedCallback;
                Eegeo::Helpers::TCallback1<SearchMenuController, int> m_onSearchItemSelectedCallback;
                Eegeo::Helpers::TCallback0<SearchMenuController> m_onModalBackgroundTappedCallback;
                Eegeo::Helpers::TCallback1<SearchMenuController, const OpenSearchMenuMessage&> m_onOpenSearchMenuHandler;
                Eegeo::Helpers::TCallback1<SearchMenuController, const Automation::OpenSearchMenuSectionMessage&> m_onOpenSearchMenuSectionHandler;

                void OnSearchItemAdded(Menu::View::MenuItemModel& item);
                
                void OnSearchItemRemoved(Menu::View::MenuItemModel& item);
                
                void OnOpenStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);
                
                void OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message);
                
                void OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message);

                void OnSearchQueryResultsRemovedMessage(const Search::SearchQueryResultsRemovedMessage& message);
                
                void OnSearchItemSelectedMessage(const Automation::SelectMenuItemMessage& message);
                
                void OnSearch(const std::string& searchQuery);
                
                bool TryDrag();
                
                void OnViewClicked();
                
                void OnSearchCleared();
                
                void OnSearchItemSelected(int& index);
                
                void OnModalBackgroundTapped();

                void OnOpenSearchMenuMessage(const OpenSearchMenuMessage& message);
                
                void OnOpenSearchMenuSectionMessage(const Automation::OpenSearchMenuSectionMessage& message);

            protected:
                
                virtual void RefreshPresentation(bool forceRefresh);
                bool IsFullyOpen() const;
                void UpdateOpenState();
                
            public:
                SearchMenuController(Menu::View::IMenuModel& model,
                                     Menu::View::IMenuViewModel& viewModel,
                                     Menu::View::IMenuView& view,
                                     ISearchMenuView& searchMenuView,
                                     Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                     TagSearch::View::ITagSearchRepository& tagSearchRepository,
                                     Modality::View::IModalBackgroundView& modalBackgroundView,
                                     ExampleAppMessaging::TMessageBus& messageBus);
                
                virtual ~SearchMenuController();
            };
        }
    }
}
