// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

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

                virtual Modality::View::IModalBackgroundView& GetModalBackgroundView() const = 0;
            };
        }
    }
}
