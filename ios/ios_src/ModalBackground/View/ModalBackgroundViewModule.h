// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IModalBackgroundViewModule.h"
#include "Modality.h"
#include "ModalBackgroundViewIncludes.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            class ModalBackgroundViewModule: public IModalBackgroundViewModule, private Eegeo::NonCopyable
            {
            private:
                ModalBackgroundView* m_pView;
                Modality::View::ModalBackgroundController* m_pController;

            public:
                ModalBackgroundViewModule(Modality::View::IModalityModel& modalityModel, const Eegeo::Rendering::ScreenProperties& screenProperties);
                ~ModalBackgroundViewModule();

                ExampleApp::Modality::View::IModalBackgroundView& GetModalBackgroundViewInterop();
                
                ModalBackgroundView& GetModalBackgroundView();
            };
        }
    }
}
