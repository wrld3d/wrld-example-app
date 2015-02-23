// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonViewModule.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            FlattenButtonViewModule::FlattenButtonViewModule(
                AndroidNativeState& nativeState,
                IFlattenButtonViewModel& viewModel,
                ExampleAppMessaging::TMessageBus& messageBus
            )
            {
                ASSERT_UI_THREAD

                m_pView = Eegeo_NEW(FlattenButtonView)(nativeState);

                m_pController = Eegeo_NEW(FlattenButtonController)(
                                    viewModel,
                                    *m_pView,
                                    messageBus
                                );

            }

            FlattenButtonViewModule::~FlattenButtonViewModule()
            {
                ASSERT_UI_THREAD
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }
        }
    }
}
