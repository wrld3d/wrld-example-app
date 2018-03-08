// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "CallbackCollection.h"
#include "ISearchWidgetView.h"
#include "SearchServices.h"
#include "SearchQueryRefreshedMessage.h"
#include "IMenuSectionsViewModel.h"
#include "IUpdateableViewController.h"

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

                Eegeo::Helpers::TCallback0<SearchWidgetController> m_onSearchResultsClearedCallback;
                Eegeo::Helpers::TCallback1<SearchWidgetController, int> m_onSearchResultSelectedCallback;
				Eegeo::Helpers::TCallback1<SearchWidgetController, const Search::SearchQueryRefreshedMessage&>
																		m_onSearchQueryRefreshedHandler;

                Eegeo::Helpers::TCallback1<SearchWidgetController, const AppModes::AppModeChangedMessage&> m_onAppModeChanged;
                Eegeo::Helpers::TCallback2<SearchWidgetController, int, int> m_onItemSelectedCallback;
                Eegeo::Helpers::TCallback1<SearchWidgetController, Menu::View::MenuItemModel> m_onItemAddedCallback;
                Eegeo::Helpers::TCallback1<SearchWidgetController, Menu::View::MenuItemModel> m_onItemRemovedCallback;

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
                virtual void OnItemSelected(int& sectionIndex, int& itemIndex);

            protected:
                virtual void OnItemAdded(Menu::View::MenuItemModel& item);
                virtual void OnItemRemoved(Menu::View::MenuItemModel& item);
            };
        }
    }
}
