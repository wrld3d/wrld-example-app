// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchTransitionPinSelectionHandler.h"

#include "CameraState.h"
#include "IAppCameraController.h"
#include "ICameraTransitionController.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowSearchTransitionPinSelectionHandler::SwallowSearchTransitionPinSelectionHandler(const SwallowTransitionResultModel& transitionResult,
                                                                                                       CameraTransitions::SdkModel::ICameraTransitionController& transitionController,
                                                                                                       AppCamera::SdkModel::IAppCameraController& appCameraController)
                : m_transitionResult(transitionResult)
                , m_transitionController(transitionController)
                , m_appCameraController(appCameraController)
                {
                    
                }
                
                void SwallowSearchTransitionPinSelectionHandler::SelectPin()
                {
                    Eegeo::Camera::CameraState cameraState = m_appCameraController.GetCameraState();
                    float distanceToInterest = (cameraState.LocationEcef()-cameraState.InterestPointEcef()).Length();
                    m_transitionController.StartTransitionTo(m_transitionResult.GetTargetLatLong().ToECEF(), distanceToInterest,  m_transitionResult.GetTargetInteriorId(), m_transitionResult.GetTargetInteriorFloor());
                }
            }
        }
    }
}