// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinSelectionHandler.h"

#include "AppCamera.h"
#include "SwallowTransitionResultModel.h"
#include "CameraTransitions.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class SwallowSearchTransitionPinSelectionHandler : public WorldPins::SdkModel::IWorldPinSelectionHandler
                {
                public:
                    SwallowSearchTransitionPinSelectionHandler(const SwallowTransitionResultModel& transitionResult,
                                                               CameraTransitions::SdkModel::ICameraTransitionController& transitionController,
                                                               AppCamera::SdkModel::IAppCameraController& appCameraController
                                                               );
                    
                    void SelectPin();
                private:
                    CameraTransitions::SdkModel::ICameraTransitionController& m_transitionController;
                    SwallowTransitionResultModel m_transitionResult;
                    AppCamera::SdkModel::IAppCameraController& m_appCameraController;
                };
            }
        }
    }
}