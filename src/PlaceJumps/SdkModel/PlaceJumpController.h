// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IPlaceJumpController.h"
#include "PlaceJumps.h"
#include "CameraTransitions.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace SdkModel
        {
            class PlaceJumpController : public IPlaceJumpController
            {
            public:
                PlaceJumpController(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController);

                void JumpTo(const View::IPlaceJumpModel& jumpModel);

            private:
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
            };
        }

    }
}
