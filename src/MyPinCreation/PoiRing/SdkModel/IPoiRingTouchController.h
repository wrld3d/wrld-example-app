// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AppInterface.h"
#include "Camera.h"
#include "GpsGlobeCameraController.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            class IPoiRingTouchController
            {
            public:
                
                virtual ~IPoiRingTouchController(){}
                
                virtual bool HandleTouchDown(const AppInterface::TouchData& data, const Eegeo::Camera::RenderCamera& renderCamera, Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController) = 0;
                virtual bool HandleTouchUp(const AppInterface::TouchData& data) = 0;
                virtual bool HandleTouchMove(const AppInterface::TouchData& data, const Eegeo::Camera::RenderCamera& renderCamera, Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController) = 0;
                
                virtual bool IsDragging() const = 0;
            };
        }
    }
}