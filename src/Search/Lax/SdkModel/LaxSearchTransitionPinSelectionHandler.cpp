// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "LaxSearchTransitionPinSelectionHandler.h"

#include "CameraState.h"
#include "IAppCameraController.h"
#include "ICameraTransitionController.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                LaxSearchTransitionPinSelectionHandler::LaxSearchTransitionPinSelectionHandler(const LaxTransitionResultModel& transitionResult,
                                                                                                       CameraTransitions::SdkModel::ICameraTransitionController& transitionController,
                                                                                                       AppCamera::SdkModel::IAppCameraController& appCameraController)
                : m_transitionResult(transitionResult)
                , m_transitionController(transitionController)
                , m_appCameraController(appCameraController)
                {
                    
                }
                
                
                void LaxSearchTransitionPinSelectionHandler::SelectPin()
                {
                    Eegeo::Camera::CameraState cameraState = m_appCameraController.GetCameraState();
                    float distanceToInterest = static_cast<float>((cameraState.LocationEcef()-cameraState.InterestPointEcef()).Length());
                    m_transitionController.StartTransitionTo(m_transitionResult.GetTargetLatLong().ToECEF(), distanceToInterest,  m_transitionResult.GetTargetInteriorId(), m_transitionResult.GetTargetInteriorFloor());
                }
            }
        }
    }
}