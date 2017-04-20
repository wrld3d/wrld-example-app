// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiController.h"
#include "SearchResultPoiViewOpenedMessage.h"
#include "SearchJsonParser.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {   
            void SearchResultPoiController::OnViewOpened()
            {
                if(!m_viewModel.TryAcquireReactorControl())
                {
                    if (m_viewModel.IsOpen())
                    {
                        m_viewModel.Close();
                    }
                    return;
                }

                const Search::SdkModel::SearchResultModel& searchResultModel = m_viewModel.GetSearchResultModel();
                
                m_metricsService.SetEvent("Opened POI",
                                          "Title", searchResultModel.GetTitle().c_str(),
                                          "Tag", searchResultModel.GetPrimaryTag().c_str(),
                                          "Vicinity", searchResultModel.GetSubtitle().c_str());
                
                m_view.Show(searchResultModel, m_viewModel.IsPinned());
                
                std::string imageUrl = "";
                Search::SdkModel::TryParseImageDetails(searchResultModel, imageUrl);
                m_messageBus.Publish(SearchResultPoiViewOpenedMessage(imageUrl));
            }

            void SearchResultPoiController::OnViewClosed()
            {
                m_view.Hide();

                m_messageBus.Publish(SearchResultPoiViewClosedMessage());
            }

            void SearchResultPoiController::OnCloseButtonClicked()
            {
                m_viewModel.Close();
            }
            
            void SearchResultPoiController::OnPinToggledButtonClicked(Search::SdkModel::SearchResultModel& searchResultModel)
            {
                m_viewModel.ToggleIsPinned();
                m_messageBus.Publish(SearchResultPoiPinToggledMessage(searchResultModel));
            }
            
            void SearchResultPoiController::OnSearchResultImageLoaded(const SearchResultPoiViewImageDownloadCompletedMessage& message)
            {
                const std::vector<Byte>* pDownloadedImageData = message.GetImageBytes();
                
                // The view may have closed while we were waiting for the download.
                if (m_viewModel.IsOpen())
                {
                    std::string imageUrl = "";
                    Search::SdkModel::TryParseImageDetails(m_viewModel.GetSearchResultModel(), imageUrl);
                    
                    // We may have closed the view and opened a new view, so check it's the same image...
                    const bool isCorrectImageUrl = (imageUrl == message.GetImageUrl());
                
                    if(isCorrectImageUrl)
                    {
                        m_view.UpdateImage(message.GetImageUrl(), message.IsSuccess(), pDownloadedImageData);
                    }
                }
                
                // The view will copy and manage the image data buffer; we must release the original here.
                Eegeo_DELETE pDownloadedImageData;
            }
            
            void SearchResultPoiController::OnClosePoiMessageRecieved(const Automation::ClosePoiMessage& message)
            {
                m_viewModel.Close();
            }

            SearchResultPoiController::SearchResultPoiController(ISearchResultPoiView& view,
                                                                 ISearchResultPoiViewModel& viewModel,
                                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                                 Metrics::IMetricsService& metricsService)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_viewOpenedCallback(this, &SearchResultPoiController::OnViewOpened)
                , m_viewClosedCallback(this, &SearchResultPoiController::OnViewClosed)
                , m_closeButtonCallback(this, &SearchResultPoiController::OnCloseButtonClicked)
                , m_togglePinnedCallback(this, &SearchResultPoiController::OnPinToggledButtonClicked)
                , m_imageLoadedHandlerBinding(this, &SearchResultPoiController::OnSearchResultImageLoaded)
                , m_closePoiMessageHandler(this, &SearchResultPoiController::OnClosePoiMessageRecieved)
            {
                m_view.InsertClosedCallback(m_closeButtonCallback);
                m_view.InsertTogglePinnedCallback(m_togglePinnedCallback);
                m_viewModel.InsertOpenedCallback(m_viewOpenedCallback);
                m_viewModel.InsertClosedCallback(m_viewClosedCallback);
                m_messageBus.SubscribeUi(m_imageLoadedHandlerBinding);
                m_messageBus.SubscribeUi(m_closePoiMessageHandler);
            }
            
            SearchResultPoiController::~SearchResultPoiController()
            {
                m_messageBus.UnsubscribeUi(m_closePoiMessageHandler);
                m_messageBus.UnsubscribeUi(m_imageLoadedHandlerBinding);
                m_viewModel.RemoveClosedCallback(m_viewClosedCallback);
                m_viewModel.RemoveOpenedCallback(m_viewOpenedCallback);
                m_view.RemoveTogglePinnedCallback(m_togglePinnedCallback);
                m_view.RemoveClosedCallback(m_closeButtonCallback);
            }
        }
    }
}
