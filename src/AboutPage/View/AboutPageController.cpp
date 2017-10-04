// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageController.h"

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
                    m_view.SetContent(m_viewModel.GetContent(false));
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
            
            void AboutPageController::OnLogoLongPress()
            {
                if (m_viewModel.TryAcquireReactorControl())
                {
                    m_view.SetContent(m_viewModel.GetContent(true));
                }
            }
            
            void AboutPageController::OnAboutPageIndoorPositionTypeMessage(const AboutPage::AboutPageIndoorPositionTypeMessage& message)
            {
                m_viewModel.SetIndoorPositioningType(message.GetIndoorPositioningType());
            }

            void AboutPageController::OnAboutPageIndoorPositionSettingsMessage(const AboutPage::AboutPageIndoorPositionSettingsMessage& message)
            {
                m_viewModel.SetIndoorPositionSettings(message.GetApiKey(), message.GetApiSecret(), message.GetFloorMap(), message.GetInteriorId());
            }

            void AboutPageController::OnAboutPageSenionDataMessage(const AboutPage::AboutPageSenionDataMessage& message)
            {
                m_viewModel.SetSenionData(message.GetEegeoFloorNumber(), message.GetSenionFloorNumber(), message.GetSenionLatitude(), message.GetSenionLongitude());
            }

            void AboutPageController::OnAboutPageIndoorAtlasDataMessage(const AboutPage::AboutPageIndoorAtlasDataMessage& message)
            {
                m_viewModel.SetIndoorAtlasData(message.GetEegeoFloorIndex(), message.GetIndoorAtlasFloorId(), message.GetLatitude(), message.GetLongitude());
            }

            void AboutPageController::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
            {
                if (message.GetAppMode() == AppModes::SdkModel::AppMode::AttractMode && m_viewModel.IsOpen())
                {
                    m_viewModel.Close();
                }
            }

            AboutPageController::AboutPageController(IAboutPageView& view, IAboutPageViewModel& viewModel,
                                                     Metrics::IMetricsService& metricsService,
                                                     ExampleAppMessaging::TMessageBus& messageBus)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_metricsService(metricsService)
                , m_viewClosed(this, &AboutPageController::OnClose)
                , m_viewOpened(this, &AboutPageController::OnOpen)
                , m_viewCloseTapped(this, &AboutPageController::OnCloseTapped)
                , m_logoLongPress(this, &AboutPageController::OnLogoLongPress)
                , m_messageBus(messageBus)
                , m_aboutPageIndoorPositionTypeMessageHandler(this, &AboutPageController::OnAboutPageIndoorPositionTypeMessage)
                , m_aboutPageIndoorPositionSettingsMessageHandler(this, &AboutPageController::OnAboutPageIndoorPositionSettingsMessage)
                , m_aboutPageSenionDataMessageHandler(this, &AboutPageController::OnAboutPageSenionDataMessage)
                , m_aboutPageIndoorAtlasDataMessageHandler(this, &AboutPageController::OnAboutPageIndoorAtlasDataMessage)
                , m_appModeChangedMessageHandler(this, &AboutPageController::OnAppModeChanged)
            {
                m_view.InsertCloseTappedCallback(m_viewCloseTapped);
                m_viewModel.InsertClosedCallback(m_viewClosed);
                m_viewModel.InsertOpenedCallback(m_viewOpened);
                m_view.InsertLogoLongPressCallback(m_logoLongPress);
                m_messageBus.SubscribeUi(m_aboutPageIndoorPositionTypeMessageHandler);
                m_messageBus.SubscribeUi(m_aboutPageIndoorPositionSettingsMessageHandler);
                m_messageBus.SubscribeUi(m_aboutPageSenionDataMessageHandler);
                m_messageBus.SubscribeUi(m_aboutPageIndoorAtlasDataMessageHandler);
                m_messageBus.SubscribeUi(m_appModeChangedMessageHandler);
            }

            AboutPageController::~AboutPageController()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedMessageHandler);
                m_messageBus.UnsubscribeUi(m_aboutPageIndoorAtlasDataMessageHandler);
                m_messageBus.UnsubscribeUi(m_aboutPageSenionDataMessageHandler);
                m_messageBus.UnsubscribeUi(m_aboutPageIndoorPositionSettingsMessageHandler);
                m_messageBus.UnsubscribeUi(m_aboutPageIndoorPositionTypeMessageHandler);
                m_view.RemoveLogoLongPressCallback(m_logoLongPress);
                m_viewModel.RemoveOpenedCallback(m_viewOpened);
                m_viewModel.RemoveClosedCallback(m_viewClosed);
                m_view.RemoveCloseTappedCallback(m_viewCloseTapped);
            }
        }
    }
}
