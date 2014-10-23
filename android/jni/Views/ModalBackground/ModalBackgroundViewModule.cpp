// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ModalBackgroundViewModule.h"
#include "Modality.h"
#include "ModalBackgroundViewController.h"
#include "RenderableFilters.h"

#include "RenderingModule.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        ModalBackgroundViewModule::ModalBackgroundViewModule(
			AndroidNativeState& nativeState,
			Modality::IModalityModel& modalityModel,
			Eegeo::Modules::Core::RenderingModule& renderingModule
		)
        : m_renderableFilters(renderingModule.GetRenderableFilters())
        {
        	m_pModalBackgroundView = Eegeo_NEW(ModalBackgroundView)(
        			renderingModule.GetShaderIdGenerator(),
        			renderingModule.GetMaterialIdGenerator(),
        			renderingModule.GetGlBufferPool(),
        			renderingModule.GetVertexLayoutPool(),
        			renderingModule.GetVertexBindingPool());

            m_pModalBackgroundViewController = Eegeo_NEW(ModalBackgroundViewController)(
				nativeState,
				modalityModel,
				*m_pModalBackgroundView
            );

            m_renderableFilters.AddRenderableFilter(*m_pModalBackgroundView);
        }
        
        ModalBackgroundViewModule::~ModalBackgroundViewModule()
        {
            Eegeo_DELETE(m_pModalBackgroundViewController);

        	m_renderableFilters.RemoveRenderableFilter(*m_pModalBackgroundView);
        	Eegeo_DELETE(m_pModalBackgroundView);
        }
        
        IModalBackgroundViewController& ModalBackgroundViewModule::GetModalBackgroundViewController() const
        {
            return *m_pModalBackgroundViewController;
        }
    }
}
