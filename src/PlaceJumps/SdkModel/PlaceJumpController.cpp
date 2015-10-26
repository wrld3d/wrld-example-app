// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PlaceJumpController.h"
#include "IPlaceJumpsModel.h"
#include "LatLongAltitude.h"
#include "Types.h"
#include "ICameraTransitionController.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace SdkModel
        {
            PlaceJumpController::PlaceJumpController(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController)
                : m_cameraTransitionController(cameraTransitionController)
            {
            }

            void PlaceJumpController::JumpTo(const View::IPlaceJumpModel& jumpModel)
            {
                m_cameraTransitionController.StartTransitionTo(jumpModel.GetLocation().ToECEF(), jumpModel.GetDistance(), Eegeo::Math::Deg2Rad(jumpModel.GetHeadingDegrees()));
            }
        }
    }
}
