// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "Modality.h"
#include "ModalBackgroundViewIncludes.h"
#include "IModalBackgroundViewModule.h"
#include "ModalBackgroundView.h"
#include "Rendering.h"
#include "Modules.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        class ModalBackgroundViewModule: public IModalBackgroundViewModule, private Eegeo::NonCopyable
        {
        private:
            ModalBackgroundViewController* m_pModalBackgroundViewController;
            ModalBackgroundView* m_pModalBackgroundView;
            
            Eegeo::Rendering::RenderableFilters& m_renderableFilters;

        public:
            ModalBackgroundViewModule(
				AndroidNativeState& nativeState,
				Modality::IModalityModel& modalityModel,
				Eegeo::Modules::Core::RenderingModule& renderingModule
        	);
            
            ~ModalBackgroundViewModule();
            
            IModalBackgroundViewController& GetModalBackgroundViewController() const;
        };
    }
}
