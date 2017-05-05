// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DesktopSearchResultPoiController.h"
#include "SearchResultPoiViewOpenedMessage.h"
#include "SearchResultPoiViewClosedMessage.h"
#include "SearchJsonParser.h"
#include "DesktopSearchResultPoiViewModel.h"
#include "SearchResultPoiControllerHelpers.h"
#include "SwallowSearchConstants.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            DesktopSearchResultPoiController::DesktopSearchResultPoiController(ISearchResultPoiView& view,
                                                                               ISearchResultPoiViewModel& viewModel,
                                                                               SearchMenu::View::ISearchMenuView& searchMenuView,
                                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                                               Metrics::IMetricsService& metricsService,
                                                                               MyPinCreation::View::IMyPinCreationInitiationView& pinCreationInitiationView,
                                                                               Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel):
                SearchResultPoiController(view,
                                          viewModel,
                                          messageBus,
                                          metricsService)
                , m_pinCreationInitiationView(pinCreationInitiationView)
                , m_onPinCreationSelected(this, &DesktopSearchResultPoiController::OnPinCreationSelectedOrSearchCleared)
                , m_interiorChangedCallback(this, &DesktopSearchResultPoiController::OnInteriorSelectionChanged)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_searchMenuView(searchMenuView)
                , m_searchClearedCallback(this, &DesktopSearchResultPoiController::OnPinCreationSelectedOrSearchCleared)
                , m_appModeChangedHandler(this, &DesktopSearchResultPoiController::OnAppModeChangedMessage)
            {
                m_pinCreationInitiationView.InsertSelectedCallback(m_onPinCreationSelected);
                
                m_interiorSelectionModel.RegisterSelectionChangedCallback(m_interiorChangedCallback);

                m_searchMenuView.InsertSearchClearedCallback(m_searchClearedCallback);

                GetMessageBus().SubscribeUi(m_appModeChangedHandler);
            }

            DesktopSearchResultPoiController::~DesktopSearchResultPoiController()
            {
                GetMessageBus().UnsubscribeUi(m_appModeChangedHandler);

                m_searchMenuView.RemoveSearchClearedCallback(m_searchClearedCallback);

                m_interiorSelectionModel.UnregisterSelectionChangedCallback(m_interiorChangedCallback);

                m_pinCreationInitiationView.RemoveSelectedCallback(m_onPinCreationSelected);
            }

            void DesktopSearchResultPoiController::OnInteriorSelectionChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                ISearchResultPoiViewModel& viewModel = GetViewModel();

                if (viewModel.IsOpen())
                {
                    viewModel.Close();
                }
            }
            
            void DesktopSearchResultPoiController::OnPinCreationSelectedOrSearchCleared()
            {
                ISearchResultPoiViewModel& viewModel = GetViewModel();

                if (viewModel.IsOpen())
                {
                    viewModel.Close();
                }
            }

            void DesktopSearchResultPoiController::OnViewOpened()
            {
                const Search::SdkModel::SearchResultModel& searchResultModel = GetViewModel().GetSearchResultModel();

                std::string floorRanges;

                if (searchResultModel.GetPrimaryTag() == Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME)
                {
                    floorRanges = "\n\n" + Helpers::GetFormattedFloorRanges(searchResultModel.GetJsonData());
                }

                Search::SdkModel::SearchResultModel newModel(0.0,
                    searchResultModel.GetIdentifier(),
                    searchResultModel.GetTitle(),
                    searchResultModel.GetSubtitle() + floorRanges,
                    searchResultModel.GetLocation(),
                    searchResultModel.GetHeightAboveTerrainMetres(),
                    searchResultModel.IsInterior(),
                    searchResultModel.GetBuildingId(),
                    searchResultModel.GetFloor(),
                    searchResultModel.GetTags(),
                    searchResultModel.GetHumanReadableTags(),
                    searchResultModel.GetIconKey(),
                    searchResultModel.GetVendor(),
                    searchResultModel.GetJsonData(),
                    Eegeo::Helpers::Time::MillisecondsSinceEpoch());
                
                GetView().Show(newModel, GetViewModel().IsPinned());

                std::string imageUrl = "";
                Search::SdkModel::TryParseImageDetails(searchResultModel, imageUrl);
                GetMessageBus().Publish(SearchResultPoiViewOpenedMessage(imageUrl));
            }

            void DesktopSearchResultPoiController::OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message)
            {
                const bool appModeAllowsOpen = message.GetAppMode() != AppModes::SdkModel::AttractMode;

                if (!appModeAllowsOpen)
                {
                    ISearchResultPoiViewModel& viewModel = GetViewModel();

                    if (viewModel.IsOpen())
                    {
                        viewModel.Close();
                    }
                }
            }
        }
    }
}
