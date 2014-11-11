// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ModalBackgroundNativeViewModule.h"
#include "RenderableFilters.h"
#include "RenderingModule.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
    	ModalBackgroundNativeViewModule::ModalBackgroundNativeViewModule(
			Eegeo::Modules::Core::RenderingModule& renderingModule,
			ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageCatalog
		)
        : m_renderableFilters(renderingModule.GetRenderableFilters())
        {
    		ASSERT_NATIVE_THREAD

        	m_pModalBackgroundView = Eegeo_NEW(ModalBackgroundView)(
				renderingModule.GetShaderIdGenerator(),
				renderingModule.GetMaterialIdGenerator(),
				renderingModule.GetGlBufferPool(),
				renderingModule.GetVertexLayoutPool(),
				renderingModule.GetVertexBindingPool()
        	);

            m_renderableFilters.AddRenderableFilter(*m_pModalBackgroundView);

            m_pModalBackgroundNativeModalityObserver = Eegeo_NEW(ModalBackgroundNativeModalityObserver)(
				*m_pModalBackgroundView,
				uiToNativeMessageCatalog
			);
        }

    	ModalBackgroundNativeViewModule::~ModalBackgroundNativeViewModule()
        {
    		ASSERT_NATIVE_THREAD

    		Eegeo_DELETE m_pModalBackgroundNativeModalityObserver;

        	m_renderableFilters.RemoveRenderableFilter(*m_pModalBackgroundView);
        	Eegeo_DELETE(m_pModalBackgroundView);
        }
    }
}
