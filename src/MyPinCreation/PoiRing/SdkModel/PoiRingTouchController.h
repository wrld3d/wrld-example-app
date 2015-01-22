// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinCreation.h"
#include "IPoiRingTouchController.h"
#include "AppInterface.h"
#include "IRayPicker.h"
#include "Camera.h"
#include "GpsGlobeCameraController.h"
#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                class PoiRingTouchController : public IPoiRingTouchController
                {
                public:
                    PoiRingTouchController(MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel,
                                           Eegeo::Resources::Terrain::Collision::IRayPicker& rayPicker,
                                           const IPoiRingController& poiRingController);

                    bool HandleTouchDown(const AppInterface::TouchData& data, const Eegeo::Camera::RenderCamera& renderCamera, Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);
                    bool HandleTouchUp(const AppInterface::TouchData& data);
                    bool HandleTouchMove(const AppInterface::TouchData& data, const Eegeo::Camera::RenderCamera& renderCamera, Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);

                    bool IsDragging() const;

                private:
                    MyPinCreation::SdkModel::IMyPinCreationModel& m_myPinCreationModel;
                    Eegeo::Resources::Terrain::Collision::IRayPicker& m_rayPicker;
                    const IPoiRingController& m_poiRingController;

                    bool m_isDragging;

                    bool PerformRayPick(Eegeo::dv3& rayOrigin, Eegeo::dv3& rayDirection, Eegeo::dv3& out_rayIntersectionPoint, double& out_intersectionParam);
                };
            }
        }
    }
}
