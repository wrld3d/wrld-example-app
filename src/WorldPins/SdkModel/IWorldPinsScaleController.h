// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Camera.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class IWorldPinsScaleController
            {
            public:
                virtual ~IWorldPinsScaleController() { }

                virtual void Update(float deltaSeconds, const Eegeo::Camera::RenderCamera& renderCamera) = 0;

                virtual void SetModality(float modality) = 0;
                
                virtual int GetVisibilityMask() = 0;
                
                virtual void SetVisibilityMask(int visibilityMask) = 0;
                
                virtual void SetHideOutdoorPinsIndoors(bool hideOutdoorPinsIndoors) = 0;
            };
        }
    }
}
