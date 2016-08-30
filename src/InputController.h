// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Types.h"
#include "IInputController.h"
#include "EegeoWorld.h"
#include "IAppCameraController.h"
#include "UserInteractionModel.h"
#include "IInitialExperienceModel.h"
#include "IPoiRingTouchController.h"
#include "IWorldPinsService.h"
#include "IAppModeModel.h"
#include "IInteriorsEntitiesPinsController.h"
#include "IDoubleTapIndoorInteractionController.h"

namespace ExampleApp
{
    class InputController : public IInputController, private Eegeo::NonCopyable
    {
    public:
        InputController(const std::shared_ptr<Eegeo::EegeoWorld>& world,
                        const std::shared_ptr<AppModes::SdkModel::IAppModeModel>& appModeModel,
                        const std::shared_ptr<AppCamera::SdkModel::IAppCameraController> cameraController,
                        const std::shared_ptr<UserInteraction::SdkModel::UserInteractionModel>& userInteractionModel,
                        const std::shared_ptr<InitialExperience::SdkModel::IInitialExperienceModel>& initialExperienceModel,
                        const std::shared_ptr<MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController>& poiRingTouchController,
                        const std::shared_ptr<WorldPins::SdkModel::IWorldPinsService>& worldPinsService,
                        const std::shared_ptr<InteriorsEntitiesPins::SdkModel::IInteriorsEntitiesPinsController>& interiorEntitiesPinsController,
                        const std::shared_ptr<DoubleTapIndoorInteraction::SdkModel::IDoubleTapIndoorInteractionController>& doubleTapIndoorInteractionController);
  
        void Event_TouchRotate 			(const AppInterface::RotateData& data);
        void Event_TouchRotate_Start	(const AppInterface::RotateData& data);
        void Event_TouchRotate_End 		(const AppInterface::RotateData& data);
        
        void Event_TouchPinch 			(const AppInterface::PinchData& data);
        void Event_TouchPinch_Start 	(const AppInterface::PinchData& data);
        void Event_TouchPinch_End 		(const AppInterface::PinchData& data);
        
        void Event_TouchPan				(const AppInterface::PanData& data);
        void Event_TouchPan_Start		(const AppInterface::PanData& data);
        void Event_TouchPan_End 		(const AppInterface::PanData& data);
        
        void Event_TouchTap 			(const AppInterface::TapData& data);
        void Event_TouchDoubleTap		(const AppInterface::TapData& data);
        
        void Event_TouchDown 			(const AppInterface::TouchData& data);
        void Event_TouchMove 			(const AppInterface::TouchData& data);
        void Event_TouchUp 				(const AppInterface::TouchData& data);
        
        void Event_Zoom                 (const AppInterface::ZoomData& data);
        void Event_Keyboard             (const AppInterface::KeyboardData& data);
        
        void Event_TiltStart            (const AppInterface::TiltData& data);
        void Event_TiltEnd              (const AppInterface::TiltData& data);
        void Event_Tilt                 (const AppInterface::TiltData& data);
        
    private:
        const std::shared_ptr<Eegeo::EegeoWorld> m_world;
        const std::shared_ptr<AppCamera::SdkModel::IAppCameraController> m_cameraController;
        const std::shared_ptr<UserInteraction::SdkModel::UserInteractionModel> m_userInteractionModel;
        const std::shared_ptr<InitialExperience::SdkModel::IInitialExperienceModel> m_initialExperienceModel;
        const std::shared_ptr<MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController> m_poiRingTouchController;
        const std::shared_ptr<WorldPins::SdkModel::IWorldPinsService> m_worldPinsService;
        const std::shared_ptr<AppModes::SdkModel::IAppModeModel> m_appModeModel;
        const std::shared_ptr<InteriorsEntitiesPins::SdkModel::IInteriorsEntitiesPinsController> m_interiorEntitiesPinsController;
        const std::shared_ptr<DoubleTapIndoorInteraction::SdkModel::IDoubleTapIndoorInteractionController> m_doubleTapIndoorInteractionController;

        
        bool CanAcceptTouch() const;
    };
}