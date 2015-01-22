// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiController.h"

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
                m_view.Show(m_viewModel.GetSearchResultModel());
            }

            void SearchResultPoiController::OnViewClosed()
            {
                m_view.Hide();
            }

            void SearchResultPoiController::OnCloseButtonClicked()
            {
                m_viewModel.Close();
            }

            SearchResultPoiController::~SearchResultPoiController()
            {
                m_viewModel.RemoveClosedCallback(m_viewClosedCallback);
                m_viewModel.RemoveClosedCallback(m_viewOpenedCallback);
                m_view.RemoveClosedCallback(m_closeButtonCallback);
            }

            SearchResultPoiController::SearchResultPoiController(ISearchResultPoiView& view, ISearchResultPoiViewModel& viewModel)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_viewOpenedCallback(this, &SearchResultPoiController::OnViewOpened)
                , m_viewClosedCallback(this, &SearchResultPoiController::OnViewClosed)
                , m_closeButtonCallback(this, &SearchResultPoiController::OnCloseButtonClicked)
            {
                m_view.InsertClosedCallback(m_closeButtonCallback);
                m_viewModel.InsertOpenedCallback(m_viewOpenedCallback);
                m_viewModel.InsertClosedCallback(m_viewClosedCallback);
            }
        }
    }
}
