// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "AboutPage.h"
#include "ICallback.h"
#include "IAboutPageViewModel.h"
#include "IAboutPageView.h"
#include "IMetricsService.h"
#include "AboutPageIndoorPositionTypeMessage.h"
#include "AboutPageSenionDataMessage.h"
#include "AboutPageIndoorPositionSettingsMessage.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            class AboutPageController : private Eegeo::NonCopyable
            {
            private:
                IAboutPageView& m_view;
                IAboutPageViewModel& m_viewModel;

                Eegeo::Helpers::TCallback0<AboutPageController> m_viewOpened;
                Eegeo::Helpers::TCallback0<AboutPageController> m_viewClosed;
                Eegeo::Helpers::TCallback0<AboutPageController> m_viewCloseTapped;
                Eegeo::Helpers::TCallback0<AboutPageController> m_logoLongPress;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Metrics::IMetricsService& m_metricsService;
                
                Eegeo::Helpers::TCallback1<AboutPageController, const AboutPageIndoorPositionTypeMessage&> m_aboutPageIndoorPositionTypeMessageHandler;
                Eegeo::Helpers::TCallback1<AboutPageController, const AboutPageIndoorPositionSettingsMessage&> m_aboutPageIndoorPositionSettingsMessageHandler;
                Eegeo::Helpers::TCallback1<AboutPageController, const AboutPageSenionDataMessage&> m_aboutPageSenionDataMessageHandler;
                Eegeo::Helpers::TCallback1<AboutPageController, const AboutPageIndoorAtlasDataMessage&> m_aboutPageIndoorAtlasDataMessageHandler;
                Eegeo::Helpers::TCallback1<AboutPageController, const AppModes::AppModeChangedMessage&> m_appModeChangedMessageHandler;

                void OnOpen();
                void OnClose();
                void OnCloseTapped();
                void OnLogoLongPress();
                
                void OnAboutPageIndoorPositionTypeMessage(const AboutPage::AboutPageIndoorPositionTypeMessage& message);
                void OnAboutPageIndoorPositionSettingsMessage(const AboutPage::AboutPageIndoorPositionSettingsMessage& message);
                void OnAboutPageSenionDataMessage(const AboutPage::AboutPageSenionDataMessage& message);
                void OnAboutPageIndoorAtlasDataMessage(const AboutPage::AboutPageIndoorAtlasDataMessage& message);
                void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);

            public:
                AboutPageController(IAboutPageView& view, IAboutPageViewModel& viewModel, Metrics::IMetricsService& metricsService, ExampleAppMessaging::TMessageBus& messageBus);

                ~AboutPageController();
            };
        }
    }
}
