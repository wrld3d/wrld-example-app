// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IModalityModel.h"
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
            ModalBackgroundViewModule(Modality::IModalityModel& modalityModel);
            
            ~ModalBackgroundViewModule();
            
            ModalBackgroundViewController& GetModalBackgroundViewController() const;
            
            ModalBackgroundView& GetModalBackgroundView() const;
        };
    }
}
