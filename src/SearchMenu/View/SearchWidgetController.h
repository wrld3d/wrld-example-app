// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "CallbackCollection.h"
#include "ISearchWidgetView.h"
#include "SearchServices.h"
#include "SearchQueryRefreshedMessage.h"
#include "IMenuSectionsViewModel.h"
#include "TagSearchAddedMessage.h"
#include "TagSearchSwallowLoadedMessage.h"
#include "IUpdateableViewController.h"

#include <map>

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchWidgetController:  public ViewControllerUpdater::View::IUpdateableViewController {
            private:
                ISearchWidgetView& m_view;
                Menu::View::IMenuSectionsViewModel& m_viewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
				SearchServices& m_searchServices;

				typedef std::map<std::string, std::string> TTagMap;
				TTagMap m_knownTags;
				TTagMap m_visibleTextOfTag;

                Eegeo::Helpers::TCallback0<SearchWidgetController> m_onSearchResultsClearedCallback;
                Eegeo::Helpers::TCallback1<SearchWidgetController, int> m_onSearchResultSelectedCallback;
				Eegeo::Helpers::TCallback1<SearchWidgetController, const Search::SearchQueryRefreshedMessage&>
																		m_onSearchQueryRefreshedHandler;

                Eegeo::Helpers::TCallback1<SearchWidgetController, const AppModes::AppModeChangedMessage&> m_onAppModeChanged;
                Eegeo::Helpers::TCallback3<SearchWidgetController, const std::string&, int, int> m_onItemSelectedCallback;
                Eegeo::Helpers::TCallback1<SearchWidgetController, Menu::View::MenuItemModel> m_onItemAddedCallback;
                Eegeo::Helpers::TCallback1<SearchWidgetController, Menu::View::MenuItemModel> m_onItemRemovedCallback;

				Eegeo::Helpers::TCallback1<SearchWidgetController, const TagSearch::TagSearchAddedMessage&> m_onTagSearchAddedHandler;
				Eegeo::Helpers::TCallback1<SearchWidgetController, const TagSearch::TagSearchSwallowLoadedMessage&> m_onTagSearchSwallowLoadedHandler;

                void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);
                bool m_menuContentsChanged;

            public:
                SearchWidgetController(ISearchWidgetView& view,
                                        SearchServices& searchServices,
                                       Menu::View::IMenuSectionsViewModel& viewModel,
                                       ExampleAppMessaging::TMessageBus& messageBus);
                ~SearchWidgetController();

                void OnSearchResultsCleared();
                void OnSearchResultSelected(int& index);
				void OnSearchQueryRefreshedMessage(const Search::SearchQueryRefreshedMessage& message);

                void RefreshPresentation(bool forceRefresh);
                virtual void UpdateUiThread(float dt);
                virtual void OnItemSelected(const std::string& menuText, int& sectionIndex, int& itemIndex);

            protected:
                virtual void OnItemAdded(Menu::View::MenuItemModel& item);
                virtual void OnItemRemoved(Menu::View::MenuItemModel& item);

				void OnTagSearchAdded(const TagSearch::TagSearchAddedMessage& message);
				void OnTagSearchSwallowLoaded(const TagSearch::TagSearchSwallowLoadedMessage& message);
				void RememberTag(const std::string& key, const std::string& tag);
            };
        }
    }
}
