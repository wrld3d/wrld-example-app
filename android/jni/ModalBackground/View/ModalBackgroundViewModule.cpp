// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundViewModule.h"
#include "ModalBackgroundController.h"
#include "ModalBackgroundAggregateView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            ModalBackgroundViewModule::ModalBackgroundViewModule(
                AndroidNativeState& nativeState,
                Modality::View::IModalityModel& modalityModel,
                ExampleAppMessaging::TMessageBus& messageBus
            )
            {
                ASSERT_UI_THREAD

                m_pView = Eegeo_NEW(ModalBackgroundAggregateView)(nativeState, messageBus);
                m_pController = Eegeo_NEW(Modality::View::ModalBackgroundController)(*m_pView, modalityModel);
            }

            ModalBackgroundViewModule::~ModalBackgroundViewModule()
            {
                ASSERT_UI_THREAD

                Eegeo_DELETE(m_pController);
                Eegeo_DELETE(m_pView);
            }

            Modality::View::IModalBackgroundView& ModalBackgroundViewModule::GetModalBackgroundView() const
            {
            	return *m_pView;
            }
        }
    }
}
