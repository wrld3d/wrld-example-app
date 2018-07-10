// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchWidgetController.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "SearchServicesResult.h"
#include "IMenuSectionViewModel.h"
#include "NavigateToMessage.h"
#include "IMenuView.h"
#include "IMenuOption.h"
#include "MenuItemModel.h"
#include "IMenuModel.h"
#include "ISearchResultsRepository.h"
#include "SearchNavigationData.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetController::SearchWidgetController(ISearchWidgetView& view,
                                                           ISearchResultsRepository& resultsRepository,
														   Modality::View::IModalBackgroundView& modalBackgroundView,
                                                           Menu::View::IMenuViewModel& viewModel,
                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                           ISearchProvider& searchProvider)
            : m_view(view)
			, m_modalBackgroundView(modalBackgroundView)
            , m_viewModel(viewModel)
            , m_messageBus(messageBus)
            , m_resultsRepository(resultsRepository)
            , m_onSearchResultsClearedCallback(this, &SearchWidgetController::OnSearchResultsCleared)
            , m_onSearchResultSelectedCallback(this, &SearchWidgetController::OnSearchResultSelected)
            , m_onNavigationRequestedCallback(this, &SearchWidgetController::OnNavigationRequested)
            , m_onSearchQueryClearRequestHandler(this, &SearchWidgetController::OnSearchQueryClearRequest)
            , m_onSearchQueryRefreshedHandler(this, &SearchWidgetController::OnSearchQueryRefreshedMessage)
            , m_onSearchQueryResultsLoadedHandler(this, &SearchWidgetController::OnSearchResultsLoaded)
            , m_deepLinkRequestedHandler(this, &SearchWidgetController::OnSearchRequestedMessage)
            , m_menuContentsChanged(true)
			, m_inInteriorMode(false)
            , m_onAppModeChanged(this, &SearchWidgetController::OnAppModeChanged)
            , m_onItemSelectedCallback(this, &SearchWidgetController::OnItemSelected)
            , m_onItemAddedCallback(this, &SearchWidgetController::OnItemAdded)
            , m_onItemRemovedCallback(this, &SearchWidgetController::OnItemRemoved)
            , m_onScreenStateChanged(this, &SearchWidgetController::OnScreenControlStateChanged)
            , m_onOpenableStateChanged(this, &SearchWidgetController::OnOpenableStateChanged)
			, m_onModalBackgroundTouchCallback(this, &SearchWidgetController::OnModalBackgroundTouch)
            , m_onViewOpenedCallback(this, &SearchWidgetController::OnViewOpened)
            , m_onViewClosedCallback(this, &SearchWidgetController::OnViewClosed)
			, m_tagCollection(m_messageBus)
			, m_previousVisibleTextFromTagSearch("")
            , m_shouldSelectFirstResult(false)
            {
                m_view.InsertSearchClearedCallback(m_onSearchResultsClearedCallback);
				m_view.InsertResultSelectedCallback(m_onSearchResultSelectedCallback);
                m_view.InsertOnItemSelected(m_onItemSelectedCallback);
                m_view.InsertOnViewClosed(m_onViewClosedCallback);
                m_view.InsertOnViewOpened(m_onViewOpenedCallback);
                m_view.InsertOnNavigationRequestedCallback(m_onNavigationRequestedCallback);

                m_viewModel.InsertOpenStateChangedCallback(m_onOpenableStateChanged);
                m_viewModel.InsertOnScreenStateChangedCallback(m_onScreenStateChanged);

				m_modalBackgroundView.InsertTouchCallback(m_onModalBackgroundTouchCallback);

                m_messageBus.SubscribeUi(m_onSearchQueryRefreshedHandler);
                
                m_messageBus.SubscribeUi(m_onSearchQueryResultsLoadedHandler);
                m_messageBus.SubscribeUi(m_onSearchQueryClearRequestHandler);
                m_messageBus.SubscribeUi(m_deepLinkRequestedHandler);
                m_messageBus.SubscribeUi(m_onAppModeChanged);

                for(size_t i = 0; i < m_viewModel.SectionsCount(); ++ i)
                {
                    Menu::View::IMenuSectionViewModel& section(m_viewModel.GetMenuSection(static_cast<int>(i)));
					SetGroupStart(section);
                    Menu::View::IMenuModel& menuModel = section.GetModel();
                    menuModel.InsertItemAddedCallback(m_onItemAddedCallback);
                    menuModel.InsertItemRemovedCallback(m_onItemRemovedCallback);
                }
                searchProvider.InsertSearchPerformedCallback(m_modalBackgroundView.GetSearchPerformedCallback());
            }

            SearchWidgetController::~SearchWidgetController()
            {
				for(int i = static_cast<int>(m_viewModel.SectionsCount()); --i >= 0;)
				{
					Menu::View::IMenuSectionViewModel& section(m_viewModel.GetMenuSection(i));
					Menu::View::IMenuModel& menuModel = section.GetModel();
					menuModel.RemoveItemAddedCallback(m_onItemAddedCallback);
					menuModel.RemoveItemRemovedCallback(m_onItemRemovedCallback);
				}

                m_messageBus.UnsubscribeUi(m_onAppModeChanged);
                m_messageBus.UnsubscribeUi(m_onSearchQueryRefreshedHandler);
                m_messageBus.UnsubscribeUi(m_onSearchQueryClearRequestHandler);
                m_messageBus.UnsubscribeUi(m_onSearchQueryResultsLoadedHandler);
                m_messageBus.UnsubscribeUi(m_deepLinkRequestedHandler);

				m_modalBackgroundView.RemoveTouchCallback(m_onModalBackgroundTouchCallback);

                m_viewModel.RemoveOnScreenStateChangedCallback(m_onScreenStateChanged);
                m_viewModel.RemoveOpenStateChangedCallback(m_onOpenableStateChanged);

                m_view.RemoveOnNavigationRequestedCallback(m_onNavigationRequestedCallback);
                m_view.RemoveOnViewClosed(m_onViewClosedCallback);
                m_view.RemoveResultSelectedCallback(m_onSearchResultSelectedCallback);
                m_view.RemoveSearchClearedCallback(m_onSearchResultsClearedCallback);
                m_view.RemoveOnItemSelected(m_onItemSelectedCallback);
                m_view.RemoveOnItemSelected(m_onItemSelectedCallback);
			}

			void SearchWidgetController::SetGroupStart(Menu::View::IMenuSectionViewModel& section)
			{
				if (section.Name() == "Find" ||
					section.Name() == "Drop Pin" ||
					section.Name() == "Weather")
				{
					section.SetGroupStart(true);
				}
            }

            void SearchWidgetController::OnItemAdded(Menu::View::MenuItemModel& item) {
                m_menuContentsChanged = true;
            }

            void SearchWidgetController::OnItemRemoved(Menu::View::MenuItemModel& item){
                m_menuContentsChanged = true;
            }

            void SearchWidgetController::OnSearchResultsCleared()
            {
                m_messageBus.Publish(SearchResultSection::SearchResultViewClearedMessage());
            }

            void SearchWidgetController::OnSearchResultSelected(int& index)
            {
                const SearchServicesResult::TSdkSearchResult& sdkSearchResult = m_resultsRepository.GetSdkSearchResultByIndex(index);

                m_messageBus.Publish(SearchResultSection::SearchResultSectionItemSelectedMessage(
                    sdkSearchResult.GetLocation().ToECEF(),
                    sdkSearchResult.IsInterior(),
                    sdkSearchResult.GetBuildingId(),
                    sdkSearchResult.GetFloor(),
                    m_resultsRepository.GetResultOriginalIndexFromCurrentIndex(index),
                    sdkSearchResult.GetIdentifier()));
            }

            void SearchWidgetController::OnNavigationRequested(const int& index)
            {
                const SearchServicesResult::TSdkSearchResult& sdkSearchResult = m_resultsRepository.GetSdkSearchResultByIndex(index);
                const NavRouting::SearchNavigationData searchNavigationData(sdkSearchResult);
                m_messageBus.Publish(NavRouting::NavigateToMessage(searchNavigationData));
            }
            
            void SearchWidgetController::OnSearchResultsLoaded(const Search::SearchQueryResponseReceivedMessage& message)
            {
                if (m_shouldSelectFirstResult && message.GetResults().size() > 0){
                    int val = 0;
                    OnSearchResultSelected(val);
                    m_shouldSelectFirstResult = false;
                }
            }

            void SearchWidgetController::OnSearchQueryRefreshedMessage(const Search::SearchQueryRefreshedMessage& message)
            {
                const Search::SdkModel::SearchQuery &query = message.Query();

				std::string visibleText = query.Query();
				std::string tagText     = "";

				if (query.IsTag())
				{
					tagText     = visibleText;
					visibleText = m_previousVisibleTextFromTagSearch;
				}

                m_view.PerformSearch(visibleText,
                                     QueryContext(false,
                                                  query.IsTag(),
                                                  tagText,
                                                  query.ShouldTryInteriorSearch(),
                                                  message.Location(),
                                                  message.Radius()));
            }

            void SearchWidgetController::OnSearchQueryClearRequest(const Search::SearchQueryClearRequestMessage &message)
            {
                m_view.ClearSearchResults();
            }
           
            void SearchWidgetController::OnSearchRequestedMessage(const Search::SearchQueryRequestMessage& message)
            {
                // needed to avoid a reentrant call on the reactor logic on startup queries / deeplinks
                m_view.CloseMenu();

                auto query = message.Query();
                auto clearPreviousResults = false;
                std::string visibleText = query.Query();
                std::string tagText = "";

                if (query.IsTag())
                {
                    tagText = visibleText;
                    
                    if (m_tagCollection.HasText(tagText))
                    {
                        const TagCollection::TagInfo& tagInfo = m_tagCollection.GetInfoByTag(tagText);
                        
                        visibleText = tagInfo.VisibleText();
                    }
                }

                m_previousVisibleTextFromTagSearch = visibleText;

                auto queryContext = QueryContext(clearPreviousResults,
                                                 query.IsTag(),
                                                 tagText,
                                                 query.ShouldTryInteriorSearch(),
                                                 query.Location(),
                                                 query.Radius());
                m_shouldSelectFirstResult = query.SelectFirstResult();
                m_view.PerformSearch(visibleText, queryContext);
            }
            
            void SearchWidgetController::UpdateUiThread(float dt)
            {
				RefreshPresentation();
            }

            void SearchWidgetController::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
            {
				m_menuContentsChanged = true;
				m_inInteriorMode = message.GetAppMode() == AppModes::SdkModel::AppMode::InteriorMode;

                RefreshPresentation();
            }

            void SearchWidgetController::OnItemSelected(const std::string& menuText, int& sectionIndex, int& itemIndex)
            {
                Menu::View::IMenuSectionViewModel& section = m_viewModel.GetMenuSection(sectionIndex);

				if (m_tagCollection.HasTag(menuText))
				{
					m_view.ClearSearchResults();

					TagCollection::TagInfo tagInfo = m_tagCollection.GetInfoByText(menuText);
					m_previousVisibleTextFromTagSearch = menuText;

					m_view.PerformSearch(menuText,
										 QueryContext(true, true, tagInfo.Tag(),
													  tagInfo.ShouldTryInterior()));
				}
                else if(!section.IsExpandable() || section.GetTotalItemCount()>0)
                {
                    section.GetItemAtIndex(itemIndex).MenuOption().Select();
                }
            }

            void SearchWidgetController::RefreshPresentation()
            {
                if (!m_menuContentsChanged)
                {
                    return;
                }
                m_menuContentsChanged = false;

                const size_t numSections = m_viewModel.SectionsCount();
                Menu::View::TSections sections;
                sections.reserve(numSections);

                for(size_t groupIndex = 0; groupIndex < numSections; groupIndex++)
                {
                    Menu::View::IMenuSectionViewModel& section = m_viewModel.GetMenuSection(static_cast<int>(groupIndex));

					if (section.Name() != "Discover" || !m_inInteriorMode)
					{
						sections.push_back(&section);
					}
                }

                m_view.UpdateMenuSectionViews(sections);
            }

            void SearchWidgetController::OnOpenableStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel)
            {
                if(m_viewModel.IsOnScreen())
                {
                    if (m_viewModel.IsOpen())
                    {
                        m_view.SetOnScreen();
                    }
                }
                else
                {
                    m_view.SetOffScreen();
                }
            }

            void SearchWidgetController::OnScreenControlStateChanged(ScreenControl::View::IScreenControlViewModel& viewModel)
            {
                if (m_viewModel.IsOnScreen())
                {
                    m_view.SetOnScreen();
                }
                else if (m_viewModel.IsOffScreen())
                {
                    m_view.SetOffScreen();
                }
            }

            void SearchWidgetController::OnViewOpened()
            {
                if(!m_viewModel.IsOpen())
                {
                    m_viewModel.Open();
                }
            }

            void SearchWidgetController::OnViewClosed()
            {
                if(!m_viewModel.IsClosed())
                {
                    m_viewModel.Close();
                }
            }

			void SearchWidgetController::OnModalBackgroundTouch()
			{
				// the modal background goes away after the first touch, so no need to throttle

				m_view.CloseMenu();
			}
        }
    }
}
