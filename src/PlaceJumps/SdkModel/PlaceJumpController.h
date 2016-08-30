// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IPlaceJumpController.h"
#include "PlaceJumps.h"
#include "CameraTransitions.h"
#include <memory>

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace SdkModel
        {
            class PlaceJumpController : public IPlaceJumpController, private Eegeo::NonCopyable
            {
            public:
                PlaceJumpController(const std::shared_ptr<CameraTransitions::SdkModel::ICameraTransitionController>& cameraTransitionController);

                void JumpTo(const View::IPlaceJumpModel& jumpModel);

            private:
                const std::shared_ptr<CameraTransitions::SdkModel::ICameraTransitionController> m_cameraTransitionController;
            };
        }

    }
}
