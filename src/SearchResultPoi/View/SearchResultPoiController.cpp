// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiController.h"
#include "FlurryWrapper.h"

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
                FLURRY_SET_EVENT("Opened POI",
                                 "Title", searchResultModel.GetTitle().c_str(),
                                 "Category", searchResultModel.GetCategory().c_str(),
                                 "Vicinity", searchResultModel.GetVicinity().c_str());
                
                m_view.Show(m_viewModel.GetSearchResultModel(), m_viewModel.IsPinned());
            }

            void SearchResultPoiController::OnViewClosed()
            {
                m_view.Hide();
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

            SearchResultPoiController::SearchResultPoiController(ISearchResultPoiView& view,
                                                                 ISearchResultPoiViewModel& viewModel,
                                                                 ExampleAppMessaging::TMessageBus& messageBus)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_messageBus(messageBus)
                , m_viewOpenedCallback(this, &SearchResultPoiController::OnViewOpened)
                , m_viewClosedCallback(this, &SearchResultPoiController::OnViewClosed)
                , m_closeButtonCallback(this, &SearchResultPoiController::OnCloseButtonClicked)
                , m_togglePinnedCallback(this, &SearchResultPoiController::OnPinToggledButtonClicked)
            {
                m_view.InsertClosedCallback(m_closeButtonCallback);
                m_view.InsertTogglePinnedCallback(m_togglePinnedCallback);
                m_viewModel.InsertOpenedCallback(m_viewOpenedCallback);
                m_viewModel.InsertClosedCallback(m_viewClosedCallback);
            }
            
            SearchResultPoiController::~SearchResultPoiController()
            {
                m_viewModel.RemoveClosedCallback(m_viewClosedCallback);
                m_viewModel.RemoveOpenedCallback(m_viewOpenedCallback);
                m_view.RemoveTogglePinnedCallback(m_togglePinnedCallback);
                m_view.RemoveClosedCallback(m_closeButtonCallback);
            }
        }
    }
}
