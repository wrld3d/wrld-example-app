// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundNativeViewModule.h"
#include "RenderableFilters.h"
#include "RenderingModule.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace SdkModel
        {
            ModalBackgroundNativeViewModule::ModalBackgroundNativeViewModule(
                Eegeo::Modules::Core::RenderingModule& renderingModule,
                ExampleAppMessaging::TMessageBus& messageBus
            )
                : m_renderableFilters(renderingModule.GetRenderableFilters())
            {
                ASSERT_NATIVE_THREAD

                m_pModalBackgroundView = Eegeo_NEW(ModalBackgroundNativeView)(
                                             renderingModule.GetShaderIdGenerator(),
                                             renderingModule.GetMaterialIdGenerator(),
                                             renderingModule.GetGlBufferPool(),
                                             renderingModule.GetVertexLayoutPool(),
                                             renderingModule.GetVertexBindingPool()
                                         );

                m_renderableFilters.AddRenderableFilter(*m_pModalBackgroundView);

                m_pModalBackgroundNativeModalityObserver = Eegeo_NEW(ModalBackgroundNativeModalityObserver)(
                            *m_pModalBackgroundView,
                            messageBus
                        );
            }

            ModalBackgroundNativeViewModule::~ModalBackgroundNativeViewModule()
            {
                ASSERT_NATIVE_THREAD

                Eegeo_DELETE m_pModalBackgroundNativeModalityObserver;

                m_renderableFilters.RemoveRenderableFilter(*m_pModalBackgroundView);
                Eegeo_DELETE(m_pModalBackgroundView);
            }

            void ModalBackgroundNativeViewModule::Update(float dt)
            {
                m_pModalBackgroundView->Update(dt);
            }
        }
    }
}
