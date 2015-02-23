// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ModalBackgroundViewIncludes.h"

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

                virtual ModalBackgroundView& GetModalBackgroundView() = 0;
            };
        }
    }
}
