// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once



#include "IWorldPinSelectionHandler.h"

#include "AppCamera.h"

#include "LaxTransitionResultModel.h"

#include "CameraTransitions.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                class LaxSearchTransitionPinSelectionHandler : public WorldPins::SdkModel::IWorldPinSelectionHandler
                {
                public:
                    LaxSearchTransitionPinSelectionHandler(const LaxTransitionResultModel& transitionResult,
                                                               CameraTransitions::SdkModel::ICameraTransitionController& transitionController,
                                                               AppCamera::SdkModel::IAppCameraController& appCameraController
                                                               );
                    
                    void SelectPin();
                private:
                    CameraTransitions::SdkModel::ICameraTransitionController& m_transitionController;
                    LaxTransitionResultModel m_transitionResult;
                    AppCamera::SdkModel::IAppCameraController& m_appCameraController;
                };
            }
        }
    }
}