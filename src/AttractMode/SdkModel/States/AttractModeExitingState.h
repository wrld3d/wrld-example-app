// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "AppModes.h"
#include "CameraTransitions.h"
#include "CatmullRomSpline.h"
#include "IAppCameraController.h"
#include "IStateMachineState.h"

namespace ExampleApp
{
    namespace AttractMode
    {
        namespace SdkModel
        {
            namespace States
            {
                class AttractModeExitingState : public Helpers::IStateMachineState
                {
                private:
                    AppModes::States::SdkModel::AttractState& m_attractState;
                    AppCamera::SdkModel::IAppCameraController& m_cameraController;
                    Eegeo::Location::ILocationService& m_locationService;
                    const int m_worldCameraHandle;
                    AppCamera::SdkModel::AppGlobeCameraWrapper& m_worldCameraController;
                    Eegeo::Resources::Interiors::InteriorsCameraController& m_interiorsCameraController;
                    Eegeo::Geometry::CatmullRomSpline& m_cameraPositionPoints;

                public:
                    AttractModeExitingState(AppModes::States::SdkModel::AttractState& attractState,
                                            AppCamera::SdkModel::IAppCameraController& cameraController,
                                            Eegeo::Location::ILocationService& locationService,
                                            const int worldCameraHandle,
                                            AppCamera::SdkModel::AppGlobeCameraWrapper& worldCameraController,
                                            Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                            Eegeo::Geometry::CatmullRomSpline& cameraPositionPoints);

                    void Enter(int previousState);
                    void Update(float dt);
                    void Exit(int nextState);
                };
            }
        }
    }
}
