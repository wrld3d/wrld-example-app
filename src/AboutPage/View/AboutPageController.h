// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "AboutPage.h"
#include "ICallback.h"
#include "IAboutPageViewModel.h"
#include "IAboutPageView.h"
#include "IMetricsService.h"
#include "AboutPageIndoorPositionTypeMessage.h"
#include "AboutPageSenionDataTypeMessage.h"
#include "AboutPageSenionSettingsTypeMessage.h"
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
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Metrics::IMetricsService& m_metricsService;
                
                Eegeo::Helpers::TCallback1<AboutPageController, const AboutPageIndoorPositionTypeMessage&> m_aboutPageIndoorPositionTypeMessage;
                
                Eegeo::Helpers::TCallback1<AboutPageController, const AboutPageSenionDataTypeMessage&> m_aboutPageSenionDataTypeMessage;
                
                Eegeo::Helpers::TCallback1<AboutPageController, const AboutPageSenionSettingsTypeMessage&> m_aboutPageSenionSettingsMessage;

                void OnOpen();

                void OnClose();

                void OnCloseTapped();
                
                void OnAboutPageIndoorPositionTypeMessageChanged(const AboutPage::AboutPageIndoorPositionTypeMessage& aboutPageIndoorPositionTypeMessage);
                
                void OnAboutPageSenionDataTypeMessageChanged(const AboutPage::AboutPageSenionDataTypeMessage& aboutPageSenionDataTypeMessage);
                
                void OnAboutPageSenionSettingsMessageChanged(const AboutPage::AboutPageSenionSettingsTypeMessage& aboutPageSenionSettingsMessage);
            public:
                AboutPageController(IAboutPageView& view, IAboutPageViewModel& viewModel, Metrics::IMetricsService& metricsService, ExampleAppMessaging::TMessageBus& messageBus);

                ~AboutPageController();
            };
        }
    }
}
