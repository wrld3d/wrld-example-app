// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinCreation.h"
#include "IPoiRingTouchController.h"
#include "AppInterface.h"
#include "IRayPicker.h"
#include "Camera.h"
#include "GpsGlobeCameraController.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            class PoiRingTouchController : public IPoiRingTouchController
            {
            public:
                PoiRingTouchController(IMyPinCreationModel& myPinCreationModel,
                                       Eegeo::Resources::Terrain::Collision::IRayPicker& rayPicker,
                                       const IPoiRingController& poiRingController);
                
                bool HandleTouchDown(const AppInterface::TouchData& data, const Eegeo::Camera::RenderCamera& renderCamera, Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);
                bool HandleTouchUp(const AppInterface::TouchData& data);
                bool HandleTouchMove(const AppInterface::TouchData& data, const Eegeo::Camera::RenderCamera& renderCamera, Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);
                
                bool IsDragging() const;
                
            private:
                IMyPinCreationModel& m_myPinCreationModel;
                Eegeo::Resources::Terrain::Collision::IRayPicker& m_rayPicker;
                const IPoiRingController& m_poiRingController;
                
                bool m_isDragging;
            };
        }
    }
}