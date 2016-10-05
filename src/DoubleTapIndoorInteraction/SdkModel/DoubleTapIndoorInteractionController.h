// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Bounds.h"
#include "Interiors.h"
#include "IRayCaster.h"
#include "IAppModeModel.h"
#include "EarthConstants.h"
#include "TerrainRayPicker.h"
#include "IntersectionTests.h"
#include "TerrainModelModule.h"
#include "EnvironmentRayCaster.h"
#include "InteriorHeightHelpers.h"
#include "InteriorTransitionModel.h"
#include "ICameraTransitionController.h"
#include "IDoubleTapIndoorInteractionController.h"
#include "IAppCameraController.h"


namespace ExampleApp
{
    namespace DoubleTapIndoorInteraction
    {
        namespace SdkModel
        {
            
            
            class DoubleTapIndoorInteractionController : public IDoubleTapIndoorInteractionController {
            
                
            public:
                
                DoubleTapIndoorInteractionController(const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController>& interiorsCameraController,
                                                     const std::shared_ptr<ExampleApp::CameraTransitions::SdkModel::ICameraTransitionController>& cameraTransitionController,
                                                     const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel,
                                                     const std::shared_ptr<ExampleApp::AppModes::SdkModel::IAppModeModel>& appModeModel,
                                                     const std::shared_ptr<Eegeo::Resources::Interiors::InteriorTransitionModel>& interiorTransitionModel,
                                                     const std::shared_ptr<Eegeo::Collision::IRayPicker>& rayPicker,
                                                     const std::shared_ptr<AppCamera::SdkModel::IAppCameraController>& iCameraController);
                ~DoubleTapIndoorInteractionController();
                void OnDoubleTap(const AppInterface::TapData& data);
                
            private:
                
                const int m_closeDistanceOffSet;
                const int m_optimizedDistanceOffSet;
                const std::shared_ptr<ExampleApp::AppModes::SdkModel::IAppModeModel> m_appModeModel;
                const std::shared_ptr<Eegeo::Collision::IRayPicker> m_rayPicker;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorTransitionModel> m_interiorTransitionModel;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel> m_interiorInteractionModel;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController> m_interiorsCameraController;
                const std::shared_ptr<ExampleApp::CameraTransitions::SdkModel::ICameraTransitionController> m_cameraTransitionController;
                const std::shared_ptr<AppCamera::SdkModel::IAppCameraController> m_iCameraController;
    
                float CalcRecommendedOverviewDistanceForFloor();
                void ZoomIn(float distance,const AppInterface::TapData& data);
                float CalculateCloseDistanceWithRespectTo(float optimizedDistance);
                bool PerformRayPick(const Eegeo::dv3 &rayOrigin,Eegeo::dv3 &rayDirection,Eegeo::dv3 &out_rayIntersectionPoint,double &out_intersectionParam,float &out_terrainHeight,float &out_heightAboveTerrain);
 


            };
            
        }
    }
}