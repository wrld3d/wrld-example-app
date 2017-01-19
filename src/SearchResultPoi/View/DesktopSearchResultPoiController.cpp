// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DesktopSearchResultPoiController.h"
#include "SearchResultPoiViewOpenedMessage.h"
#include "SearchResultPoiViewClosedMessage.h"
#include "SearchJsonParser.h"
#include "DesktopSearchResultPoiViewModel.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            DesktopSearchResultPoiController::DesktopSearchResultPoiController(ISearchResultPoiView& view,
                                                                               ISearchResultPoiViewModel& viewModel,
                                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                                               Metrics::IMetricsService& metricsService,
                                                                               MyPinCreation::View::IMyPinCreationInitiationView& pinCreationInitiationView,
                                                                               Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                               MyPinDetails::View::IMyPinDetailsViewModel& pinDetailsViewModel):
                SearchResultPoiController(view,
                                          viewModel,
                                          messageBus,
                                          metricsService)
                , m_pinCreationInitiationView(pinCreationInitiationView)
                , m_onPinCreationSelected(this, &DesktopSearchResultPoiController::OnPinCreationSelected)
                , m_pinDetailsViewModel(pinDetailsViewModel)
                , m_onPinDetailsOpened(this, &DesktopSearchResultPoiController::OnPinDetailsOpened)
                , m_interiorChangedCallback(this, &DesktopSearchResultPoiController::OnInteriorSelectionChanged)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_appModeChangedHandler(this, &DesktopSearchResultPoiController::OnAppModeChangedMessage)
            {
                m_pinCreationInitiationView.InsertSelectedCallback(m_onPinCreationSelected);

                m_pinDetailsViewModel.InsertOpenedCallback(m_onPinDetailsOpened);
                
                m_interiorSelectionModel.RegisterSelectionChangedCallback(m_interiorChangedCallback);

                GetMessageBus().SubscribeUi(m_appModeChangedHandler);
            }

            DesktopSearchResultPoiController::~DesktopSearchResultPoiController()
            {
                GetMessageBus().UnsubscribeUi(m_appModeChangedHandler);

                m_pinCreationInitiationView.RemoveSelectedCallback(m_onPinCreationSelected);

                m_pinDetailsViewModel.RemoveOpenedCallback(m_onPinDetailsOpened);

                m_interiorSelectionModel.UnregisterSelectionChangedCallback(m_interiorChangedCallback);
            }

            void DesktopSearchResultPoiController::OnInteriorSelectionChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                ISearchResultPoiViewModel& viewModel = GetViewModel();

                if (viewModel.IsOpen())
                {
                    viewModel.Close();
                }
            }
            
            void DesktopSearchResultPoiController::OnPinCreationSelected()
            {
                ISearchResultPoiViewModel& viewModel = GetViewModel();

                if (viewModel.IsOpen())
                {
                    viewModel.Close();
                }
            }

			void DesktopSearchResultPoiController::OnPinDetailsOpened()
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

                GetView().Show(searchResultModel, GetViewModel().IsPinned());

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
