// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IPlaceJumpController.h"
#include "PlaceJumps.h"
#include "GlobeCamera.h"
#include "Compass.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        class PlaceJumpController : public IPlaceJumpController
        {
        public:
            PlaceJumpController(Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController,
                                Compass::ICompassModel& compassModel);
            
            void JumpTo(IPlaceJumpModel& jumpModel);
            
        private:
            Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_cameraController;
            Compass::ICompassModel& m_compassModel;
        };

    }
}
