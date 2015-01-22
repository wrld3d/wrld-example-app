// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PlaceJumpController.h"
#include "GpsGlobeCameraController.h"
#include "IPlaceJumpsModel.h"
#include "EcefTangentBasis.h"
#include "CameraHelpers.h"
#include "LatLongAltitude.h"
#include "Types.h"
#include "CompassModel.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace SdkModel
        {
            PlaceJumpController::PlaceJumpController(Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController,
                    Compass::SdkModel::ICompassModel& compassModel)
                : m_cameraController(globeCameraController)
                , m_compassModel(compassModel)
            {

            }

            void PlaceJumpController::JumpTo(View::IPlaceJumpModel& jumpModel)
            {
                m_compassModel.DisableGpsMode();

                Eegeo::Space::EcefTangentBasis cameraInterestBasis;
                Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(jumpModel.GetLocation().ToECEF(),
                        jumpModel.GetHeadingDegrees(),
                        cameraInterestBasis);


                m_cameraController.SetView(cameraInterestBasis, jumpModel.GetDistance());
            }
        }
    }
}
