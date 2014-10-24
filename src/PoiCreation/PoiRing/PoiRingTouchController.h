// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiCreation.h"
#include "IPoiRingTouchController.h"
#include "AppInterface.h"
#include "IRayPicker.h"
#include "Camera.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        namespace PoiRing
        {
            class PoiRingTouchController : public IPoiRingTouchController
            {
            public:
                PoiRingTouchController(IPoiCreationModel& poiCreationModel,
                                       Eegeo::Resources::Terrain::Collision::IRayPicker& rayPicker);
                
                bool HandleTouchDown(const AppInterface::TouchData& data, const Eegeo::Camera::RenderCamera& renderCamera);
                bool HandleTouchUp(const AppInterface::TouchData& data);
                bool HandleTouchMove(const AppInterface::TouchData& data, const Eegeo::Camera::RenderCamera& renderCamera);
                
                bool IsDragging() const;
                
            private:
                IPoiCreationModel& m_poiCreationModel;
                Eegeo::Resources::Terrain::Collision::IRayPicker& m_rayPicker;
                
                bool m_isDragging;
            };
        }
    }
}