// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageViewModule.h"
#include "AboutPage.h"
#include "AboutPageView.h"
#include "AboutPageController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            AboutPageViewModule::AboutPageViewModule(
                AndroidNativeState& nativeState,
                IAboutPageViewModel& aboutPageViewModel,
                Metrics::IMetricsService& metricsService,
				ExampleAppMessaging::TMessageBus& messageBus
            )
            {
                ASSERT_UI_THREAD
                m_pView = Eegeo_NEW(AboutPageView)(nativeState);
                m_pController = Eegeo_NEW(AboutPageController)(*m_pView, aboutPageViewModel, metricsService, messageBus);
            }

            AboutPageViewModule::~AboutPageViewModule()
            {
                ASSERT_UI_THREAD

                Eegeo_DELETE(m_pController);
                Eegeo_DELETE(m_pView);
            }

            AboutPageController& AboutPageViewModule::GetAboutPageController() const
            {
                ASSERT_UI_THREAD
                return *m_pController;
            }

            AboutPageView& AboutPageViewModule::GetAboutPageView() const
            {
                ASSERT_UI_THREAD
                return *m_pView;
            }
        }
    }
}
