// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageController.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            void AboutPageController::OnOpen()
            {
                if (m_viewModel.TryAcquireReactorControl())
                {
                    m_metricsService.SetEvent("UIItem: About page");
                    m_metricsService.BeginTimedEvent("TimedEvent: Viewing About Page");
                    m_view.SetContent(m_viewModel.GetContent());
                    m_view.Open();
                }
            }

            void AboutPageController::OnClose()
            {
                m_metricsService.EndTimedEvent("TimedEvent: Viewing About Page");
                m_view.Close();
            }

            void AboutPageController::OnCloseTapped()
            {
                if (m_viewModel.IsOpen())
                {
                    m_viewModel.Close();
                }
            }

            void AboutPageController::OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message)
            {
                const AppModes::SdkModel::AppMode appMode = message.GetAppMode();
                const bool appModeAllowsOpen = appMode != AppModes::SdkModel::TourMode &&
                                               appMode != AppModes::SdkModel::AttractMode;

                if (!appModeAllowsOpen)
                {
                    if (m_viewModel.IsOpen())
                    {
                        m_viewModel.Close();
                    }
                }
            }

            AboutPageController::AboutPageController(IAboutPageView& view, IAboutPageViewModel& viewModel, Metrics::IMetricsService& metricsService, ExampleAppMessaging::TMessageBus& messageBus)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_metricsService(metricsService)
                , m_viewClosed(this, &AboutPageController::OnClose)
                , m_viewOpened(this, &AboutPageController::OnOpen)
                , m_viewCloseTapped(this, &AboutPageController::OnCloseTapped)
                , m_messageBus(messageBus)
                , m_appModeChangedHandler(this, &AboutPageController::OnAppModeChangedMessage)
            {
                m_view.InsertCloseTappedCallback(m_viewCloseTapped);
                m_viewModel.InsertClosedCallback(m_viewClosed);
                m_viewModel.InsertOpenedCallback(m_viewOpened);
                m_messageBus.SubscribeUi(m_appModeChangedHandler);
            }

            AboutPageController::~AboutPageController()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedHandler);
                m_viewModel.RemoveOpenedCallback(m_viewOpened);
                m_viewModel.RemoveClosedCallback(m_viewClosed);
                m_view.RemoveCloseTappedCallback(m_viewCloseTapped);
            }
        }
    }
}
