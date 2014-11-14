// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Camera.h"
#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            class IPoiRingController
            {
            public:
                
                virtual ~IPoiRingController() {}
            
                virtual void Update(float dt, const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& cameraEcefInterestPoint) = 0;
            };
        }
    }
}