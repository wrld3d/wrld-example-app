// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiCreation.h"
#include "IPoiRingController.h"
#include "AppInterface.h"
#include "Camera.h"
#include "Terrain.h"
#include "Rendering.h"
namespace ExampleApp
{
    namespace PoiCreation
    {
        namespace PoiRing
        {
            class PoiRingController : public IPoiRingController
            {
            public:
                PoiRingController(IPoiCreationModel& poiCreationModel,
                                  PoiRingView& poiRingView,
                                  const Eegeo::Rendering::ScreenProperties& screenProperties);
            
                void Update(float dt, const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& cameraEcefInterestPoint);
                
            private:
                const Eegeo::Rendering::ScreenProperties& m_screenProperties;
                
                IPoiCreationModel& m_poiCreationModel;
                
                PoiRingView& m_poiRingView;
                
                float m_scaleInterpolationParam;
                float m_easeDurationInSeconds;
                
                Eegeo::v3 CalculateQuadScreenSpaceTranslation(const Eegeo::Camera::RenderCamera& renderCamera) const;
                float CalculateTransitionScale(float dt);
            };
        }
    }
}