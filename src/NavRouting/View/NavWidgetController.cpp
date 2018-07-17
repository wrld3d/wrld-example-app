// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetController.h"
#include "NavRoutingViewClosedMessage.h"
#include "NavRoutingSelectStartLocationClickedMessage.h"
#include "NavRoutingSelectEndLocationClickedMessage.h"
#include "NavRoutingStartLocationClearClickedMessage.h"
#include "NavRoutingEndLocationClearClickedMessage.h"
#include "NavRoutingSelectedDirectionChangedMessage.h"
#include "NavRoutingStartEndRoutingButtonClickedMessage.h"
#include "NavRoutingRerouteDialogClosedMessage.h"
#include "NavRoutingViewOpenedMessage.h"
#include "NavRoutingSetCalculatingRouteMessage.h"
#include "NavRoutingSearchForLocationMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            void NavWidgetController::OnViewOpened()
            {
                m_view.Show();
                
                m_messageBus.Publish(NavRoutingViewOpenedMessage());
            }

            void NavWidgetController::OnViewClosed()
            {
                m_view.Hide();

                m_messageBus.Publish(NavRoutingViewClosedMessage());
            }

            void NavWidgetController::OnCloseButtonClicked()
            {
                m_viewModel.Close();
            }

            void NavWidgetController::OnStartLocationClicked()
            {
                m_messageBus.Publish(NavRoutingSelectStartLocationClickedMessage());
            }

            void NavWidgetController::OnEndLocationClicked()
            {
                m_messageBus.Publish(NavRoutingSelectEndLocationClickedMessage());
            }

            void NavWidgetController::OnStartLocationClearButtonClicked()
            {
                m_messageBus.Publish(NavRoutingStartLocationClearClickedMessage());
            }

            void NavWidgetController::OnEndLocationClearButtonClicked()
            {
                m_messageBus.Publish(NavRoutingEndLocationClearClickedMessage());
            }

            void NavWidgetController::OnStartEndLocationsSwapped()
            {
                m_messageBus.Publish(NavRoutingViewStartEndLocationSwappedMessage());
            }

            void NavWidgetController::OnSelectedDirectionIndexChanged(const int& selectedDirection)
            {
                m_messageBus.Publish(NavRoutingSelectedDirectionChangedMessage(selectedDirection));
            }

            void NavWidgetController::OnRerouteDialogClosed(const bool& shouldReroute)
            {
                m_messageBus.Publish(NavRoutingRerouteDialogClosedMessage(shouldReroute));
            }

            void NavWidgetController::OnStartEndRoutingButtonClicked()
            {
                m_messageBus.Publish(NavRoutingStartEndRoutingButtonClickedMessage());
            }

            void NavWidgetController::OnStartLocationSet(const NavRoutingStartLocationSetMessage& message)
            {
                m_view.SetStartLocation(message.GetStartLocation());
            }

            void NavWidgetController::OnStartLocationCleared(const NavRoutingStartLocationClearedMessage& message)
            {
                m_view.ClearStartLocation();
            }

            void NavWidgetController::OnEndLocationSet(const NavRoutingEndLocationSetMessage& message)
            {
                m_view.SetEndLocation(message.GetEndLocation());
            }

            void NavWidgetController::OnEndLocationCleared(const NavRoutingEndLocationClearedMessage& message)
            {
                m_view.ClearEndLocation();
            }

            void NavWidgetController::OnRouteChanged(const NavRoutingRouteChangedMessage &message)
            {
                m_view.SetRoute(message.GetRouteModel(), message.GetIsNewRoute());
            }

            void NavWidgetController::OnRouteCleared(const NavRoutingRouteClearedMessage& message)
            {
                m_view.ClearRoute();
            }

            void NavWidgetController::OnCurrentDirectionSet(const NavRoutingCurrentDirectionSetMessage& message)
            {
                m_view.SetCurrentDirection(message.GetDirectionIndex());
            }

            void NavWidgetController::OnCurrentDirectionUpdated(const NavRoutingCurrentDirectionUpdatedMessage& message)
            {
                m_view.UpdateCurrentDirection(message.GetDirectionModel());
            }

            void NavWidgetController::OnSelectedDirectionSet(const NavRoutingSelectedDirectionSetMessage& message)
            {
                m_view.SetSelectedDirection(message.GetDirectionIndex());
            }

            void NavWidgetController::OnRemainingRouteDurationSet(const NavRoutingRemainingRouteDurationSetMessage& message)
            {
                m_view.SetRemainingRouteDuration(message.GetRemainingRouteDuration());
            }

            void NavWidgetController::OnNavRoutingModeSet(const NavRoutingModeSetMessage& message)
            {
                m_view.SetNavMode(message.GetNavMode());
                m_viewModel.SetNavMode(message.GetNavMode());
            }

            void NavWidgetController::OnNavRoutingViewOpen(const NavRoutingViewOpenMessage& message)
            {
                if (!m_viewModel.IsOpen())
                {
                    m_viewModel.Open();

                    //Resetting view
                    m_view.ClearRoute();
                    m_view.SetRemainingRouteDuration(0);

                    const SdkModel::INavRoutingModel& navRoutingModel = message.GetNavRoutingModel();

                    SdkModel::NavRoutingLocationModel startLocation, endLocation;

                    if (navRoutingModel.TryGetStartLocation(startLocation))
                    {
                        m_view.SetStartLocation(startLocation);
                    }
                    else
                    {
                        m_view.ClearStartLocation();
                    }

                    if (navRoutingModel.TryGetEndLocation(endLocation))
                    {
                        m_view.SetEndLocation(endLocation);
                    }
                    else
                    {
                        m_view.ClearEndLocation();
                    }
                }
            }

            void NavWidgetController::OnNavRoutingShowRerouteDialog(const NavRoutingShowRerouteDialogMessage& message)
            {
                m_view.ShowRerouteDialog(message.GetMessage());
            }

            void NavWidgetController::OnNavigationStartPointFromResult(const int& index)
            {
                const SearchMenu::View::SearchServicesResult::TSdkSearchResult& sdkSearchResult = m_searchResultsRepository.GetSdkSearchResultByIndex(index);
                const NavRouting::SearchNavigationData searchNavigationData(sdkSearchResult);
                m_messageBus.Publish(NavRoutingStartLocationSetFromSearchMessage(searchNavigationData));
            }

            void NavWidgetController::OnNavigationEndPointFromResult(const int& index)
            {
                const SearchMenu::View::SearchServicesResult::TSdkSearchResult& sdkSearchResult = m_searchResultsRepository.GetSdkSearchResultByIndex(index);
                const NavRouting::SearchNavigationData searchNavigationData(sdkSearchResult);
                m_messageBus.Publish(NavRoutingEndLocationSetFromSearchMessage(searchNavigationData));
            }

            void NavWidgetController::OnSearchingForLocationChanged(const bool &isSearching,
                                                                    const bool &isStartLocation)
            {
                m_messageBus.Publish(NavRoutingSearchForLocationMessage(isSearching, isStartLocation));
            }
            
            void NavWidgetController::OnSetCalculateRouteSpinner(const NavRoutingSetCalculatingRouteMessage& message)
            {
                if(message.GetShouldCalculatingRoute())
                {
                    m_view.ShowCalculatingRouteSpinner();
                }
                else
                {
                    m_view.HideCalculatingRouteSpinner();
                }
            }

            NavWidgetController::NavWidgetController(INavWidgetView& view,
                                                     INavWidgetViewModel& viewModel,
                                                     SearchMenu::View::ISearchResultsRepository& searchResultsRepository,
                                                     ExampleAppMessaging::TMessageBus& messageBus)
                    : m_view(view)
                    , m_viewModel(viewModel)
                    , m_messageBus(messageBus)
                    , m_closeButtonCallback(this, &NavWidgetController::OnCloseButtonClicked)
                    , m_startLocationClickedCallback(this, &NavWidgetController::OnStartLocationClicked)
                    , m_endLocationClickedCallback(this, &NavWidgetController::OnEndLocationClicked)
                    , m_startLocationClearButtonClickedCallback(this, &NavWidgetController::OnStartLocationClearButtonClicked)
                    , m_endLocationClearButtonClickedCallback(this, &NavWidgetController::OnEndLocationClearButtonClicked)
                    , m_startEndLocationsSwappedCallback(this, &NavWidgetController::OnStartEndLocationsSwapped)
                    , m_selectedDirectionIndexChangedCallback(this, &NavWidgetController::OnSelectedDirectionIndexChanged)
                    , m_rerouteDialogClosedCallback(this, &NavWidgetController::OnRerouteDialogClosed)
                    , m_startEndRoutingButtonClickedCallback(this, &NavWidgetController::OnStartEndRoutingButtonClicked)
                    , m_viewOpenedCallback(this, &NavWidgetController::OnViewOpened)
                    , m_viewClosedCallback(this, &NavWidgetController::OnViewClosed)
                    , m_startLocationSetMessageHandler(this, &NavWidgetController::OnStartLocationSet)
                    , m_startLocationClearedMessageHandler(this, &NavWidgetController::OnStartLocationCleared)
                    , m_endLocationSetMessageHandler(this, &NavWidgetController::OnEndLocationSet)
                    , m_endLocationClearedMessageHandler(this, &NavWidgetController::OnEndLocationCleared)
                    , m_routeSetMessageHandler(this, &NavWidgetController::OnRouteChanged)
                    , m_routeClearedMessageHandler(this, &NavWidgetController::OnRouteCleared)
                    , m_currentDirectionSetMessageHandler(this, &NavWidgetController::OnCurrentDirectionSet)
                    , m_currentDirectionUpdatedMessageHandler(this, &NavWidgetController::OnCurrentDirectionUpdated)
                    , m_selectedDirectionSetMessageHandler(this, &NavWidgetController::OnSelectedDirectionSet)
                    , m_remainingRouteDurationSetMessageHandler(this, &NavWidgetController::OnRemainingRouteDurationSet)
                    , m_navRoutingModeSetMessageHandler(this, &NavWidgetController::OnNavRoutingModeSet)
                    , m_navRoutingViewOpenMessageHandler(this, &NavWidgetController::OnNavRoutingViewOpen)
                    , m_navRoutingShowRerouteDialogMessageMessageHandler(this, &NavWidgetController::OnNavRoutingShowRerouteDialog)
                    , m_searchResultsRepository(searchResultsRepository)
                    , m_onNavigationStartPointFromResultCallback(this, &NavWidgetController::OnNavigationStartPointFromResult)
                    , m_onNavigationEndPointFromResultCallback(this, &NavWidgetController::OnNavigationEndPointFromResult)
                    , m_navRoutingSetCalculatingRouteMessageHandler(this, &NavWidgetController::OnSetCalculateRouteSpinner)
                    , m_onSearchingForLocationCallback(this, &NavWidgetController::OnSearchingForLocationChanged)
            {
                m_view.InsertClosedCallback(m_closeButtonCallback);
                m_view.InsertStartLocationClickedCallback(m_startLocationClickedCallback);
                m_view.InsertEndLocationClickedCallback(m_endLocationClickedCallback);
                m_view.InsertStartLocationClearButtonClickedCallback(m_startLocationClearButtonClickedCallback);
                m_view.InsertEndLocationClearButtonCallback(m_endLocationClearButtonClickedCallback);
                m_view.InsertStartEndLocationsSwappedCallback(m_startEndLocationsSwappedCallback);
                m_view.InsertSelectedDirectionIndexChangedCallback(m_selectedDirectionIndexChangedCallback);
                m_view.InsertRerouteDialogClosedCallback(m_rerouteDialogClosedCallback);
                m_view.InsertStartEndRoutingButtonClickedCallback(m_startEndRoutingButtonClickedCallback);
                m_viewModel.InsertOpenedCallback(m_viewOpenedCallback);
                m_viewModel.InsertClosedCallback(m_viewClosedCallback);
                m_messageBus.SubscribeUi(m_startLocationSetMessageHandler);
                m_messageBus.SubscribeUi(m_startLocationClearedMessageHandler);
                m_messageBus.SubscribeUi(m_endLocationSetMessageHandler);
                m_messageBus.SubscribeUi(m_endLocationClearedMessageHandler);
                m_messageBus.SubscribeUi(m_routeSetMessageHandler);
                m_messageBus.SubscribeUi(m_routeClearedMessageHandler);
                m_messageBus.SubscribeUi(m_currentDirectionSetMessageHandler);
                m_messageBus.SubscribeUi(m_currentDirectionUpdatedMessageHandler);
                m_messageBus.SubscribeUi(m_selectedDirectionSetMessageHandler);
                m_messageBus.SubscribeUi(m_remainingRouteDurationSetMessageHandler);
                m_messageBus.SubscribeUi(m_navRoutingModeSetMessageHandler);
                m_messageBus.SubscribeUi(m_navRoutingViewOpenMessageHandler);
                m_messageBus.SubscribeUi(m_navRoutingShowRerouteDialogMessageMessageHandler);
                m_messageBus.SubscribeUi(m_navRoutingSetCalculatingRouteMessageHandler);
                
                m_view.InsertOnNavigationStartPointSetFromResult(m_onNavigationStartPointFromResultCallback);
                m_view.InsertOnNavigationEndPointSetFromResult(m_onNavigationEndPointFromResultCallback);
                m_view.InsertOnSearchForLocationChanged(m_onSearchingForLocationCallback);
            }

            NavWidgetController::~NavWidgetController()
            {
                m_view.RemoveOnSearchForLocationChanged(m_onSearchingForLocationCallback);
                m_view.RemoveOnNavigationEndPointSetFromResult(m_onNavigationEndPointFromResultCallback);
                m_view.RemoveOnNavigationStartPointSetFromResult(m_onNavigationStartPointFromResultCallback);
            
                m_messageBus.UnsubscribeUi(m_navRoutingSetCalculatingRouteMessageHandler);
                m_messageBus.UnsubscribeUi(m_navRoutingShowRerouteDialogMessageMessageHandler);
                m_messageBus.UnsubscribeUi(m_navRoutingViewOpenMessageHandler);
                m_messageBus.UnsubscribeUi(m_navRoutingModeSetMessageHandler);
                m_messageBus.UnsubscribeUi(m_remainingRouteDurationSetMessageHandler);
                m_messageBus.UnsubscribeUi(m_selectedDirectionSetMessageHandler);
                m_messageBus.UnsubscribeUi(m_currentDirectionUpdatedMessageHandler);
                m_messageBus.UnsubscribeUi(m_currentDirectionSetMessageHandler);
                m_messageBus.UnsubscribeUi(m_routeClearedMessageHandler);
                m_messageBus.UnsubscribeUi(m_routeSetMessageHandler);
                m_messageBus.UnsubscribeUi(m_endLocationClearedMessageHandler);
                m_messageBus.UnsubscribeUi(m_endLocationSetMessageHandler);
                m_messageBus.UnsubscribeUi(m_startLocationClearedMessageHandler);
                m_messageBus.UnsubscribeUi(m_startLocationSetMessageHandler);
                m_viewModel.RemoveClosedCallback(m_viewClosedCallback);
                m_viewModel.RemoveOpenedCallback(m_viewOpenedCallback);
                m_view.RemoveStartEndRoutingButtonClickedCallback(m_startEndRoutingButtonClickedCallback);
                m_view.RemoveRerouteDialogClosedCallback(m_rerouteDialogClosedCallback);
                m_view.RemoveSelectedDirectionIndexChangedCallback(m_selectedDirectionIndexChangedCallback);
                m_view.RemoveStartEndLocationsSwappedCallback(m_startEndLocationsSwappedCallback);
                m_view.RemoveEndLocationClearButtonCallback(m_endLocationClearButtonClickedCallback);
                m_view.RemoveStartLocationClearButtonClickedCallback(m_startLocationClearButtonClickedCallback);
                m_view.RemoveEndLocationClickedCallback(m_endLocationClickedCallback);
                m_view.RemoveStartLocationClickedCallback(m_startLocationClickedCallback);
                m_view.RemoveClosedCallback(m_closeButtonCallback);
            }
        }
    }
}
