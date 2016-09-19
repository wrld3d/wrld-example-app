// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Bounds.h"
#include "Interiors.h"
#include "IRayCaster.h"
#include "IAppModeModel.h"
#include "EnvironmentRayCaster.h"
#include "ICameraTransitionController.h"
#include "IDoubleTapIndoorInteractionController.h"



namespace ExampleApp
{
    namespace DoubleTapIndoorInteraction
    {
        namespace SdkModel
        {
            
            enum ZoomState
            {
                Far = 0,
                Optimized,
                Close
            };
            
            class DoubleTapIndoorInteractionController : public IDoubleTapIndoorInteractionController {
            
                
            public:
                
                DoubleTapIndoorInteractionController(Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                                     ExampleApp::CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                     Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                     Eegeo::Collision::IRayCaster& rayCaster,
                                                     ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel);
                ~DoubleTapIndoorInteractionController();
                void OnDoubleTap(const AppInterface::TapData& data);
                
            private:
                
                Eegeo::Collision::IRayCaster& m_enovRayCaster;
                ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
                Eegeo::Helpers::TCallback0<DoubleTapIndoorInteractionController> m_appModeChangedCallback;
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                Eegeo::Resources::Interiors::InteriorsCameraController& m_interiorsCameraController;
                ExampleApp::CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                
                
                
                void OnAppModeChanged();
                void ZoomInTo(float distance,const AppInterface::TapData& data);
                float CalculateCloseDistanceWithRespectTo(float optimizedDistance);
                float CalcRecommendedOverviewDistanceForFloor(const Eegeo::Geometry::Bounds3D& floorTangentSpaceBounds, float fieldOfViewRadians);

                ZoomState m_states;

            };
            
        }
    }
}