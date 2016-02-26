// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ModalBackgroundViewIncludes.h"
#include "Modality.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            class IModalBackgroundViewModule
            {
            public:
                virtual ~IModalBackgroundViewModule() { }
                
                virtual ExampleApp::Modality::View::IModalBackgroundView& GetModalBackgroundViewInterop() = 0;

                virtual ModalBackgroundView& GetModalBackgroundView() = 0;
            };
        }
    }
}
