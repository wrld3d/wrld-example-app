// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "Modality.h"
#include "ModalBackgroundViewIncludes.h"
#include "IModalBackgroundViewModule.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        class ModalBackgroundViewModule: public IModalBackgroundViewModule, private Eegeo::NonCopyable
        {
        private:
            ModalBackgroundViewController* m_pModalBackgroundViewController;

        public:
            ModalBackgroundViewModule(
				AndroidNativeState& nativeState,
				Modality::IModalityModel& modalityModel
        	);
            
            ~ModalBackgroundViewModule();
            
            IModalBackgroundViewController& GetModalBackgroundViewController() const;
        };
    }
}
