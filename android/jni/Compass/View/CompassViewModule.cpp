// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassViewModule.h"
#include "CompassView.h"
#include "CompassController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            CompassViewModule::CompassViewModule(
                AndroidNativeState& nativeState,
                ICompassViewModel& viewModel,
                Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& navWidgetViewBottomHeightChangedCallbacks,
                ExampleAppMessaging::TMessageBus& messageBus
            )
            {
                ASSERT_UI_THREAD

                m_pView = Eegeo_NEW(CompassView)(nativeState, navWidgetViewBottomHeightChangedCallbacks);
                m_pController = Eegeo_NEW(CompassController)(
                                    *m_pView,
                                    viewModel,
                                    messageBus);
            }

            CompassViewModule::~CompassViewModule()
            {
                ASSERT_UI_THREAD

                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }

            ICompassView& CompassViewModule::GetCompassView()
            {
                return *m_pView;
            }
        }
    }
}
