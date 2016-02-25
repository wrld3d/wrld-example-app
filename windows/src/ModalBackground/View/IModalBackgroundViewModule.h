// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IModalBackgroundView.h"
#include "ModalBackgroundController.h"

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

                virtual Modality::View::IModalBackgroundView& GetView() = 0;
                virtual Modality::View::ModalBackgroundController& GetController() = 0;
            };
        }
    }
}
