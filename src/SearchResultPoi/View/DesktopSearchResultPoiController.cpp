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
            DesktopSearchResultPoiController::DesktopSearchResultPoiController(const std::shared_ptr<ISearchResultPoiView>& view,
                                                                               const std::shared_ptr<ISearchResultPoiViewModel>& viewModel,
                                                                               const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                                               const std::shared_ptr<Metrics::IMetricsService>& metricsService,
                                                                               const std::shared_ptr<MyPinCreation::View::IMyPinCreationInitiationView>& pinCreationInitiationView,
                                                                               const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel>& interiorSelectionModel):
                SearchResultPoiController(view,
                                          viewModel,
                                          messageBus,
                                          metricsService)
                , m_pinCreationInitiationView(pinCreationInitiationView)
                , m_onPinCreationSelected(this, &DesktopSearchResultPoiController::OnPinCreationSelected)
                , m_interiorChangedCallback(this, &DesktopSearchResultPoiController::OnInteriorSelectionChanged)
                , m_interiorSelectionModel(interiorSelectionModel)
            {
                m_pinCreationInitiationView->InsertSelectedCallback(m_onPinCreationSelected);
                
                m_interiorSelectionModel->RegisterSelectionChangedCallback(m_interiorChangedCallback);
            }

            DesktopSearchResultPoiController::~DesktopSearchResultPoiController()
            {
                m_pinCreationInitiationView->RemoveSelectedCallback(m_onPinCreationSelected);

                m_interiorSelectionModel->UnregisterSelectionChangedCallback(m_interiorChangedCallback);
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

            void DesktopSearchResultPoiController::OnViewOpened()
            {
                const Search::SdkModel::SearchResultModel& searchResultModel = GetViewModel().GetSearchResultModel();

                GetView().Show(searchResultModel, GetViewModel().IsPinned());

                std::string imageUrl = "";
                Search::SdkModel::TryParseImageDetails(searchResultModel, imageUrl);
                GetMessageBus().Publish(SearchResultPoiViewOpenedMessage(imageUrl));
            }
        }
    }
}
