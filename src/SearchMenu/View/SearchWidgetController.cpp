// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchWidgetController.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "SearchServicesResult.h"
#include "IMenuSectionViewModel.h"
#include "IMenuView.h"
#include "IMenuOption.h"
#include "MenuItemModel.h"
#include "IMenuModel.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetController::SearchWidgetController(ISearchWidgetView& view,
                                                           SearchServices& searchServices,
                                                           Menu::View::IMenuSectionsViewModel& viewModel,
                                                           ExampleAppMessaging::TMessageBus& messageBus)
            : m_view(view)
            , m_viewModel(viewModel)
            , m_messageBus(messageBus)
            , m_searchServices(searchServices)
            , m_onSearchResultsClearedCallback(this, &SearchWidgetController::OnSearchResultsCleared)
            , m_onSearchResultSelectedCallback(this, &SearchWidgetController::OnSearchResultSelected)
            , m_onSearchQueryRefreshedHandler(this, &SearchWidgetController::OnSearchQueryRefreshedMessage)
            , m_menuContentsChanged(true)
            , m_onAppModeChanged(this, &SearchWidgetController::OnAppModeChanged)
            , m_onItemSelectedCallback(this, &SearchWidgetController::OnItemSelected)
            , m_onItemAddedCallback(this, &SearchWidgetController::OnItemAdded)
            , m_onItemRemovedCallback(this, &SearchWidgetController::OnItemRemoved)
            , m_onTagSearchAddedHandler(this, &SearchWidgetController::OnTagSearchAdded)
			, m_onTagSearchSwallowLoadedHandler(this, &SearchWidgetController::OnTagSearchSwallowLoaded)
            {
                m_view.InsertSearchClearedCallback(m_onSearchResultsClearedCallback);
				m_view.InsertResultSelectedCallback(m_onSearchResultSelectedCallback);
                m_view.InsertOnItemSelected(m_onItemSelectedCallback);

                m_messageBus.SubscribeUi(m_onSearchQueryRefreshedHandler);
				m_messageBus.SubscribeUi(m_onTagSearchAddedHandler);
				m_messageBus.SubscribeUi(m_onTagSearchSwallowLoadedHandler);
                m_messageBus.SubscribeUi(m_onAppModeChanged);


                for(size_t i = 0; i < m_viewModel.SectionsCount(); ++ i)
                {
                    Menu::View::IMenuSectionViewModel& section(m_viewModel.GetMenuSection(static_cast<int>(i)));
                    Menu::View::IMenuModel& menuModel = section.GetModel();
                    menuModel.InsertItemAddedCallback(m_onItemAddedCallback);
                    menuModel.InsertItemRemovedCallback(m_onItemRemovedCallback);
                }
            }

            SearchWidgetController::~SearchWidgetController()
            {
                m_messageBus.UnsubscribeUi(m_onAppModeChanged);
				m_messageBus.UnsubscribeUi(m_onTagSearchSwallowLoadedHandler);
                m_messageBus.UnsubscribeUi(m_onTagSearchAddedHandler);
                m_messageBus.UnsubscribeUi(m_onSearchQueryRefreshedHandler);

                m_view.RemoveResultSelectedCallback(m_onSearchResultSelectedCallback);
                m_view.RemoveSearchClearedCallback(m_onSearchResultsClearedCallback);
                m_view.RemoveOnItemSelected(m_onItemSelectedCallback);
            }

            void SearchWidgetController::OnItemAdded(Menu::View::MenuItemModel& item) {
                m_menuContentsChanged = true;
            }

            void SearchWidgetController::OnItemRemoved(Menu::View::MenuItemModel& item){
                m_menuContentsChanged = true;
            }

            void SearchWidgetController::OnTagSearchAdded(const TagSearch::TagSearchAddedMessage& message)
            {
				const TagSearch::View::TagSearchModel& tagSearchModel = message.Model();

				RememberTag(tagSearchModel.Name(), tagSearchModel.SearchTag());
            }

			void SearchWidgetController::OnTagSearchSwallowLoaded(const TagSearch::TagSearchSwallowLoadedMessage& message)
			{
				RememberTag(message.Key(), message.Tag());
			}

			void SearchWidgetController::RememberTag(const std::string& key, const std::string& tag)
			{
				Eegeo_ASSERT(m_knownTags       .find(key) == m_knownTags       .end());
				Eegeo_ASSERT(m_visibleTextOfTag.find(tag) == m_visibleTextOfTag.end());

				m_knownTags       [key] = tag;
				m_visibleTextOfTag[tag] = key;
			}

            void SearchWidgetController::OnSearchResultsCleared()
            {
                m_messageBus.Publish(SearchResultSection::SearchResultViewClearedMessage());
            }

            void SearchWidgetController::OnSearchResultSelected(int& index)
            {
                const SearchServicesResult::TSdkSearchResult& sdkSearchResult = m_searchServices.GetSdkSearchResultByIndex(index);

                m_messageBus.Publish(SearchResultSection::SearchResultSectionItemSelectedMessage(
                    sdkSearchResult.GetIdentifier(),
                    sdkSearchResult.GetLocation().ToECEF(),
                    sdkSearchResult.IsInterior(),
                    sdkSearchResult.GetBuildingId(),
                    sdkSearchResult.GetFloor(),
                    m_searchServices.GetResultOriginalIndexFromCurrentIndex(index),
                    sdkSearchResult.GetIdentifier()));
            }

            void SearchWidgetController::OnSearchQueryRefreshedMessage(const Search::SearchQueryRefreshedMessage& message)
            {
                const Search::SdkModel::SearchQuery &query = message.Query();

				std::string visibleText = query.Query();
				std::string tagText     = "";

				if (query.IsTag())
				{
					TTagMap::iterator it = m_visibleTextOfTag.find(visibleText);

					Eegeo_ASSERT(it != m_visibleTextOfTag.end());

					tagText     = visibleText;
					visibleText = it->second;
				}

                m_view.PerformSearch(visibleText,
									 QueryContext(query.IsTag(),
												  tagText,
												  query.ShouldTryInteriorSearch(),
												  message.ShouldZoomToBuildingsView(),
												  message.Location(),
												  message.Radius()));
            }

            void SearchWidgetController::UpdateUiThread(float dt)
            {
                RefreshPresentation(true);
            }

            void SearchWidgetController::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
            {
                RefreshPresentation(true);

            }

            void SearchWidgetController::OnItemSelected(const std::string& menuText, int& sectionIndex, int& itemIndex){
                Menu::View::IMenuSectionViewModel& section = m_viewModel.GetMenuSection(sectionIndex);

                if(!section.IsExpandable() || section.Size()!=1)
				{
					const int index = section.IsExpandable() ? itemIndex - 1 : itemIndex;
					section.GetItemAtIndex(index).MenuOption().Select();
				}

				TTagMap::iterator it = m_knownTags.find(menuText);

				if (it != m_knownTags.end())
					m_view.PerformSearch(menuText, QueryContext(true, it->second, true, false));
            }

            void SearchWidgetController::RefreshPresentation(bool forceRefresh)
            {

               const size_t numSections = m_viewModel.SectionsCount();
                Menu::View::TSections sections;
                sections.reserve(numSections);

                for(size_t groupIndex = 0; groupIndex < numSections; groupIndex++)
                {
                    Menu::View::IMenuSectionViewModel& section = m_viewModel.GetMenuSection(static_cast<int>(groupIndex));
                    sections.push_back(&section);
                }

                if(forceRefresh)
                {
                    m_view.UpdateMenuSectionViews(sections, m_menuContentsChanged);
                    m_menuContentsChanged = false;
                }
            }
        }
    }
}