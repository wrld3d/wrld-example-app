// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            void NavWidgetController::OnViewOpened()
            {
                if(!m_viewModel.TryAcquireReactorControl())
                {
                    if (m_viewModel.IsOpen())
                    {
                        m_viewModel.Close();
                    }
                    return;
                }

                m_view.Show();
            }

            void NavWidgetController::OnViewClosed()
            {
                m_view.Hide();

                //TODO publish closed message
            }

            void NavWidgetController::OnCloseButtonClicked()
            {
                m_viewModel.Close();
            }

            void NavWidgetController::OnDirectionsButtonClicked(const SearchResultPoi::SearchResultPoiDirectionsButtonClickedMessage& message)
            {
                if (!m_viewModel.IsOpen())
                {
                    m_viewModel.Open();
                }
            }

            NavWidgetController::NavWidgetController(INavWidgetView& view,
                                                     INavWidgetViewModel& viewModel,
                                                     ExampleAppMessaging::TMessageBus& messageBus)
                    : m_view(view)
                    , m_viewModel(viewModel)
                    , m_messageBus(messageBus)
                    , m_viewOpenedCallback(this, &NavWidgetController::OnViewOpened)
                    , m_viewClosedCallback(this, &NavWidgetController::OnViewClosed)
                    , m_closeButtonCallback(this, &NavWidgetController::OnCloseButtonClicked)
                    , m_directionsButtonClickedMessageHandler(this, &NavWidgetController::OnDirectionsButtonClicked)
            {
                m_view.InsertClosedCallback(m_closeButtonCallback);
                m_viewModel.InsertOpenedCallback(m_viewOpenedCallback);
                m_viewModel.InsertClosedCallback(m_viewClosedCallback);
                m_messageBus.SubscribeUi(m_directionsButtonClickedMessageHandler);
            }

            NavWidgetController::~NavWidgetController()
            {
                m_messageBus.UnsubscribeUi(m_directionsButtonClickedMessageHandler);
                m_viewModel.RemoveClosedCallback(m_viewClosedCallback);
                m_viewModel.RemoveOpenedCallback(m_viewOpenedCallback);
                m_view.RemoveClosedCallback(m_closeButtonCallback);
            }
        }
    }
}
