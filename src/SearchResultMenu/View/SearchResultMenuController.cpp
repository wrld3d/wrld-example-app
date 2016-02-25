// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuController.h"

#include <algorithm>
#include "IAppModeModel.h"
#include "ISearchResultMenuOrder.h"
#include "SearchResultItemModel.h"
#include "SearchVendorNames.h"
#include "SwallowSearchParser.h"
#include "SwallowOfficeResultMenuOption.h"
#include "SwallowSearchConstants.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            namespace
            {
                class OrderWrapper
                {
                private:
                    ISearchResultMenuOrder& m_order;
                public:
                    OrderWrapper(ISearchResultMenuOrder& order)
                        : m_order(order)
                    {
                    }
                    
                    bool operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
                    {
                        return m_order(a, b);
                    }
                };
            }
            
            void SearchResultMenuController::OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message)
            {
                std::string headerString = CategorySearch::View::GetPresentationStringForQuery(m_categorySearchRepository, message.Query());
                m_searchView.SetHeader(headerString, true, 0);
                m_searchResultMenuViewModel.SetHasSearchQueryInFlight(true);
            }

            void SearchResultMenuController::OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message)
            {
                std::string headerString = CategorySearch::View::GetPresentationStringForQuery(m_categorySearchRepository, message.GetQuery());
                m_searchView.SetHeader(headerString, false, message.GetResults().size());
                
                for(int i = 0; i < m_lastAddedResults.size(); ++i)
                {
                    const Search::SdkModel::SearchResultModel& model(m_lastAddedResults[i]);
                    m_menuOptions.RemoveItem(model.GetIdentifier());
                }
                
                m_lastAddedResults = message.GetResults();
                OrderWrapper orderWrapper(m_order);
                std::stable_sort(m_lastAddedResults.begin(), m_lastAddedResults.end(), orderWrapper);
                
                for(int i = 0; i < m_lastAddedResults.size(); ++i)
                {
                    const Search::SdkModel::SearchResultModel& model(m_lastAddedResults[i]);
                    std::string subtitle = model.GetSubtitle();
                    if (model.GetCategory() == Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
                    {
                        // Availability is no longer a subtitle as that affects search results.
                        Search::Swallow::SdkModel::SwallowMeetingRoomResultModel meetingRoomModel = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(model);
                        subtitle = Search::Swallow::SdkModel::SearchParser::GetFormattedAvailabilityString(meetingRoomModel.GetAvailability());
                    }
                    m_menuOptions.AddItem(model.GetIdentifier(),
                                          model.GetTitle(),
                                          subtitle,
                                          model.GetCategory(),
                                          GetMenuOptionByVendor(model.GetVendor(), model));
                }
                
                m_searchResultMenuViewModel.SetHasSearchQueryInFlight(false);
            }
            
            Menu::View::IMenuOption* SearchResultMenuController::GetMenuOptionByVendor(const std::string& vendor, const Search::SdkModel::SearchResultModel& model) const
            {
                if(vendor == Search::EegeoVendorName && model.GetCategory() ==  Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME)
                {
                    Search::Swallow::SdkModel::SwallowOfficeResultModel officeModel = Search::Swallow::SdkModel::SearchParser::TransformToSwallowOfficeResult(model);
                    
                    // TODO: Add interior data to office result.
                    return Eegeo_NEW(Search::Swallow::View::SwallowOfficeResultMenuOption)(officeModel.GetName(),
                                                                                           model.GetLocation(),
                                                                                           officeModel.GetHeadingDegrees(),
                                                                                           officeModel.GetDistance(),
                                                                                           m_viewModel,
                                                                                           m_messageBus);
                }
                else
                {
                    return Eegeo_NEW(SearchResultItemModel)(model.GetTitle(),
                                                            model.GetLocation().ToECEF(),
                                                            model.IsInterior(),
                                                            model.GetBuildingId(),
                                                            model.GetFloor(),
                                                            m_viewModel,
                                                            m_messageBus);
                }
            }

            void SearchResultMenuController::OnViewClicked()
            {
                if(m_searchResultMenuViewModel.CanInteract())
                {
                    MenuController::OnViewClicked();
                }
            }

            void SearchResultMenuController::OnSearchClosed()
            {
                m_messageBus.Publish(ExampleApp::SearchResultMenu::SearchResultViewClearedMessage());
                m_viewModel.RemoveFromScreen();
            }
            
            void SearchResultMenuController::OnAttractModeChanged()
            {
                m_searchView.SetAttractMode(m_searchResultMenuViewModel.AttractModeEnabled());
            }
            
            void SearchResultMenuController::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {

            }

            SearchResultMenuController::SearchResultMenuController(
                ISearchResultMenuView& searchView,
                Menu::View::IMenuView& menuView,
                Menu::View::IMenuModel& menuModel,
                Menu::View::IMenuViewModel& menuViewModel,
                Menu::View::IMenuOptionsModel& menuOptions,
                ISearchResultMenuOrder& order,
                CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                ISearchResultMenuViewModel& searchResultMenuViewModel,
                ExampleAppMessaging::TMessageBus& messageBus)
                : MenuController(menuModel, menuViewModel, menuView, messageBus)
                , m_searchView(searchView)
                , m_menuOptions(menuOptions)
                , m_order(order)
                , m_categorySearchRepository(categorySearchRepository)
                , m_searchResultMenuViewModel(searchResultMenuViewModel)
                , m_messageBus(messageBus)
                , m_onSearchCloseTappedCallback(this, &SearchResultMenuController::OnSearchClosed)
                , m_searchQueryIssuedHandler(this, &SearchResultMenuController::OnSearchQueryPerformedMessage)
                , m_searchResultReceivedHandler(this, &SearchResultMenuController::OnSearchQueryResponseReceivedMessage)
                , m_attractModeChangedCallback(this, &SearchResultMenuController::OnAttractModeChanged)
                , m_appModeChangedCallback(this, &SearchResultMenuController::OnAppModeChanged)
            {
                m_searchView.InsertSearchClosed(m_onSearchCloseTappedCallback);
                m_messageBus.SubscribeUi(m_searchQueryIssuedHandler);
                m_messageBus.SubscribeUi(m_searchResultReceivedHandler);
                m_messageBus.SubscribeUi(m_appModeChangedCallback);
                m_searchResultMenuViewModel.InsertAttractModeChangedCallback(m_attractModeChangedCallback);

                m_messageBus.SubscribeUi(m_appModeChangedCallback);
            }

            SearchResultMenuController::~SearchResultMenuController()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
                m_searchResultMenuViewModel.RemoveAttractModeChangedCallback(m_attractModeChangedCallback);
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
                m_messageBus.UnsubscribeUi(m_searchResultReceivedHandler);
                m_messageBus.UnsubscribeUi(m_searchQueryIssuedHandler);
                m_searchView.RemoveSearchClosed(m_onSearchCloseTappedCallback);
            }
        }
    }
}
