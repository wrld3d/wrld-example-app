// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WindowsNativeState.h"
#include "Types.h"
#include "Rendering.h"
#include "ModalBackgroundNativeView.h"
#include "Modules.h"
#include "IModalBackgroundNativeViewModule.h"
#include "ModalBackgroundNativeModalityObserver.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace SdkModel
        {
            class ModalBackgroundNativeViewModule : public IModalBackgroundNativeViewModule, private Eegeo::NonCopyable
            {
            private:
                ModalBackgroundNativeView* m_pModalBackgroundView;
                ModalBackgroundNativeModalityObserver* m_pModalBackgroundNativeModalityObserver;

                Eegeo::Rendering::RenderableFilters& m_renderableFilters;

            public:
                ModalBackgroundNativeViewModule(
                    Eegeo::Modules::Core::RenderingModule& renderingModule,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                void Update(float dt);

                ~ModalBackgroundNativeViewModule();
            };
        }
    }
}
