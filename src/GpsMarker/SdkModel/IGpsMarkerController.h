// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Camera.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class IGpsMarkerController
            {
            public:
                
                virtual ~IGpsMarkerController() {}

                virtual void Update(float dt, const Eegeo::Camera::RenderCamera& renderCamera) = 0;
            };
        }
    }
}