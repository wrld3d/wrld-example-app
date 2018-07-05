// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AppCamera.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            class IAppCameraLocationPicker
            {
            public:

                virtual ~IAppCameraLocationPicker() {}

                virtual AppCameraLocationPickerResult PickLocation(float screenX, float screenY) = 0;
            };
        }
    }
}