// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetViewModule.h"
#include "NavWidgetView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            NavWidgetViewModule::NavWidgetViewModule(
                AndroidNativeState& nativeState,
                INavWidgetViewModel& navWidgetViewModel,
                Eegeo::Location::ILocationService& locationService,
                ExampleAppMessaging::TMessageBus& messageBus)
            {
                ASSERT_UI_THREAD
                m_pView = Eegeo_NEW(NavWidgetView)(nativeState);
                m_pController = Eegeo_NEW(NavWidgetController)(*m_pView, navWidgetViewModel, locationService, messageBus);
            }

            NavWidgetViewModule::~NavWidgetViewModule()
            {
                ASSERT_UI_THREAD
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }

            NavWidgetView& NavWidgetViewModule::GetView() const
            {
                return *m_pView;
            }

            NavWidgetController& NavWidgetViewModule::GetController() const
            {
                return *m_pController;
            }
        }
    }
}
