// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Camera.h"
#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                class IPoiRingController
                {
                public:

                    virtual ~IPoiRingController() {}

                    virtual void Update(float dt, const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& cameraEcefInterestPoint) = 0;

                    virtual void GetIconPositionAndSize(Eegeo::dv3& out_positionEcef, float& out_sizeMeters) const = 0;
                    virtual void GetSpherePositionAndRadius(Eegeo::dv3& out_sphereCenterEcef, float& out_sphereRadius) const = 0;
                };
            }
        }
    }
}
