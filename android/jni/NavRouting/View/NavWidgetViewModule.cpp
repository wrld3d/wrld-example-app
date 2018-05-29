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
                Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& navWidgetViewTopHeightChangedCallbacks,
                Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& navWidgetViewBottomHeightChangedCallbacks,
                ExampleAppMessaging::TMessageBus& messageBus)
            {
                ASSERT_UI_THREAD
                m_pView = Eegeo_NEW(NavWidgetView)(nativeState,
                                                   navWidgetViewTopHeightChangedCallbacks,
                                                   navWidgetViewBottomHeightChangedCallbacks);
                m_pController = Eegeo_NEW(NavWidgetController)(*m_pView, navWidgetViewModel, messageBus);
            }

            NavWidgetViewModule::~NavWidgetViewModule()
            {
                ASSERT_UI_THREAD
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }

            INavWidgetView& NavWidgetViewModule::GetView() const
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
