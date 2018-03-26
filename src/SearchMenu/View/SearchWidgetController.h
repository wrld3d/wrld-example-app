// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "CallbackCollection.h"
#include "ISearchWidgetView.h"
#include "SearchServices.h"
#include "SearchQueryRefreshedMessage.h"
#include "IMenuViewModel.h"
#include "IMenuSectionsViewModel.h"
#include "IUpdateableViewController.h"
#include "IOpenableControlViewModel.h"
#include "IScreenControlViewModel.h"
#include "IModalBackgroundView.h"
#include "TagCollection.h"

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
				Modality::View::IModalBackgroundView& m_modalBackgroundView;
                Menu::View::IMenuViewModel& m_viewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
				SearchServices& m_searchServices;

				typedef std::map<std::string, std::string> TTagMap;
				TTagMap m_knownTags;
				TTagMap m_visibleTextOfTag;

                Eegeo::Helpers::TCallback0<SearchWidgetController> m_onViewOpenedCallback;
                Eegeo::Helpers::TCallback0<SearchWidgetController> m_onViewClosedCallback;
                Eegeo::Helpers::TCallback0<SearchWidgetController> m_onSearchResultsClearedCallback;
                Eegeo::Helpers::TCallback1<SearchWidgetController, int> m_onSearchResultSelectedCallback;
				Eegeo::Helpers::TCallback1<SearchWidgetController, const Search::SearchQueryRefreshedMessage&>
																		m_onSearchQueryRefreshedHandler;
                Eegeo::Helpers::TCallback2<SearchWidgetController, ScreenControl::View::IScreenControlViewModel&, float> m_onScreenStateChanged;
                Eegeo::Helpers::TCallback2<SearchWidgetController, OpenableControl::View::IOpenableControlViewModel&, float> m_onOpenableStateChanged;
				Eegeo::Helpers::TCallback0<SearchWidgetController> m_onModalBackgroundTouchCallback;

                Eegeo::Helpers::TCallback1<SearchWidgetController, const AppModes::AppModeChangedMessage&> m_onAppModeChanged;
                Eegeo::Helpers::TCallback3<SearchWidgetController, const std::string&, int, int> m_onItemSelectedCallback;
                Eegeo::Helpers::TCallback1<SearchWidgetController, Menu::View::MenuItemModel> m_onItemAddedCallback;
                Eegeo::Helpers::TCallback1<SearchWidgetController, Menu::View::MenuItemModel> m_onItemRemovedCallback;

                bool m_menuContentsChanged;

				TagCollection m_tagCollection;

            public:
                SearchWidgetController(ISearchWidgetView& view,
                                       SearchServices& searchServices,
									   Modality::View::IModalBackgroundView& modalBackgroundView,
                                       Menu::View::IMenuViewModel& viewModel,
                                       ExampleAppMessaging::TMessageBus& messageBus);
                ~SearchWidgetController();

            protected:
				void SetGroupStart(Menu::View::IMenuSectionViewModel& section);

				void OnItemAdded(Menu::View::MenuItemModel& item);
				void OnItemRemoved(Menu::View::MenuItemModel& item);

				void OnSearchResultsCleared();
				void OnSearchResultSelected(int& index);
				void OnSearchQueryRefreshedMessage(const Search::SearchQueryRefreshedMessage& message);

				virtual void UpdateUiThread(float dt);
				void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);
				void RefreshPresentation(bool forceRefresh, bool modeChangedToInterior);

				void OnItemSelected(const std::string& menuText, int& sectionIndex, int& itemIndex);
				void OnOpenableStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel, float& state);
                void OnScreenControlStateChanged(ScreenControl::View::IScreenControlViewModel& viewModel, float& state);
				void OnViewOpened();
				void OnViewClosed();
				void OnModalBackgroundTouch();
            };
        }
    }
}
