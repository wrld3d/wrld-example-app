// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IPlaceJumpController.h"
#include "PlaceJumps.h"
#include "GlobeCamera.h"
#include "Compass.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace SdkModel
        {
            class PlaceJumpController : public IPlaceJumpController
            {
            public:
                PlaceJumpController(Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController,
                                    Compass::SdkModel::ICompassModel& compassModel);

                void JumpTo(View::IPlaceJumpModel& jumpModel);

            private:
                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_cameraController;
                Compass::SdkModel::ICompassModel& m_compassModel;
            };
        }

    }
}
