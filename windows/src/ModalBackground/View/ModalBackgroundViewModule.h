// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IModalBackgroundViewModule.h"
#include "WindowsNativeState.h"
#include "Types.h"
#include "Modality.h"
#include "ModalBackgroundViewIncludes.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            class ModalBackgroundViewModule: public IModalBackgroundViewModule, private Eegeo::NonCopyable
            {
            private:
                ModalBackgroundAggregateView* m_pView;
                Modality::View::ModalBackgroundController* m_pController;

            public:
                ModalBackgroundViewModule(
                    WindowsNativeState& nativeState,
                    Modality::View::IModalityModel& modalityModel,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~ModalBackgroundViewModule();

                Modality::View::IModalBackgroundView& GetView();
                Modality::View::ModalBackgroundController& GetController();
            };
        }
    }
}
