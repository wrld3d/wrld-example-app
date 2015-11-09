// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ModalBackgroundViewIncludes.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace SdkModel
        {
            class IModalBackgroundNativeViewModule
            {
            public:
                virtual ~IModalBackgroundNativeViewModule() { }
                virtual void Update(float dt) = 0;
            };
        }
    }
}
