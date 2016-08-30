// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "InputController.h"

namespace ExampleApp
{
    InputController::InputController(
                     const std::shared_ptr<Eegeo::EegeoWorld>& world,
                     const std::shared_ptr<AppModes::SdkModel::IAppModeModel>& appModeModel,
                     const std::shared_ptr<AppCamera::SdkModel::IAppCameraController> cameraController,
                     const std::shared_ptr<UserInteraction::SdkModel::UserInteractionModel>& userInteractionModel,
                     const std::shared_ptr<InitialExperience::SdkModel::IInitialExperienceModel>& initialExperienceModel,
                     const std::shared_ptr<MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController>& poiRingTouchController,
                     const std::shared_ptr<WorldPins::SdkModel::IWorldPinsService>& worldPinsService,
                     const std::shared_ptr<InteriorsEntitiesPins::SdkModel::IInteriorsEntitiesPinsController>& interiorEntitiesPinsController,
                     const std::shared_ptr<DoubleTapIndoorInteraction::SdkModel::IDoubleTapIndoorInteractionController>& doubleTapIndoorInteractionController)
    : m_world(world)
    , m_appModeModel(appModeModel)
    , m_cameraController(cameraController)
    , m_userInteractionModel(userInteractionModel)
    , m_initialExperienceModel(initialExperienceModel)
    , m_poiRingTouchController(poiRingTouchController)
    , m_worldPinsService(worldPinsService)
    , m_interiorEntitiesPinsController(interiorEntitiesPinsController)
    , m_doubleTapIndoorInteractionController(doubleTapIndoorInteractionController)
    {
        Eegeo_ASSERT(m_world != nullptr);
        Eegeo_ASSERT(m_appModeModel != nullptr);
        Eegeo_ASSERT(m_cameraController != nullptr);
        Eegeo_ASSERT(m_userInteractionModel != nullptr);
        Eegeo_ASSERT(m_initialExperienceModel != nullptr);
        Eegeo_ASSERT(m_worldPinsService != nullptr);
        Eegeo_ASSERT(m_interiorEntitiesPinsController != nullptr);
        Eegeo_ASSERT(m_doubleTapIndoorInteractionController != nullptr);
        Eegeo_ASSERT(m_poiRingTouchController != nullptr);
    }
    
    void InputController::Event_TouchRotate(const AppInterface::RotateData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_cameraController->GetTouchController().Event_TouchRotate(data);
        
    }
    
    void InputController::Event_TouchRotate_Start(const AppInterface::RotateData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_cameraController->GetTouchController().Event_TouchRotate_Start(data);
    }
    
    void InputController::Event_TouchRotate_End(const AppInterface::RotateData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_cameraController->GetTouchController().Event_TouchRotate_End(data);
    }
    
    void InputController::Event_TouchPinch(const AppInterface::PinchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_cameraController->GetTouchController().Event_TouchPinch(data);
    }
    
    void InputController::Event_TouchPinch_Start(const AppInterface::PinchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_cameraController->GetTouchController().Event_TouchPinch_Start(data);
    }
    
    void InputController::Event_TouchPinch_End(const AppInterface::PinchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_cameraController->GetTouchController().Event_TouchPinch_End(data);
    }
    
    void InputController::Event_TouchPan(const AppInterface::PanData& data)
    {
        if(!CanAcceptTouch() || m_poiRingTouchController->IsDragging())
        {
             return;
        }
        
        m_cameraController->GetTouchController().Event_TouchPan(data);
    }
    
    void InputController::Event_TouchPan_Start(const AppInterface::PanData& data)
    {
        if(!CanAcceptTouch() || m_poiRingTouchController->IsDragging())
        {
             return;
        }
        
        m_cameraController->GetTouchController().Event_TouchPan_Start(data);
    }
    
    void InputController::Event_TouchPan_End(const AppInterface::PanData& data)
    {
        if(!CanAcceptTouch() || m_poiRingTouchController->IsDragging())
        {
             return;
        }
        
        m_cameraController->GetTouchController().Event_TouchPan_End(data);
    }
    
    void InputController::Event_TouchTap(const AppInterface::TapData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        if(m_worldPinsService->HandleTouchTap(data.point))
        {
            return;
        }
         
        m_interiorEntitiesPinsController->Event_TouchTap(data);
        
        m_cameraController->GetTouchController().Event_TouchTap(data);
    }
    
    void InputController::Event_TouchDoubleTap(const AppInterface::TapData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        if (m_worldPinsService->HandleTouchDoubleTap(data.point))
        {
            return;
        }
        
        if (m_appModeModel->GetAppMode() == AppModes::SdkModel::InteriorMode)
        {
            m_doubleTapIndoorInteractionController->OnDoubleTap(data);
        }
        
        m_cameraController->GetTouchController().Event_TouchDoubleTap(data);
    }
    
    void InputController::Event_TouchDown(const AppInterface::TouchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        if (!m_poiRingTouchController->HandleTouchDown(data, m_cameraController->GetRenderCamera(), m_cameraController->GetNonFlattenedCameraPosition()))
        {
            m_cameraController->GetTouchController().Event_TouchDown(data);
        }
    }
    
    void InputController::Event_TouchMove(const AppInterface::TouchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        if (!m_poiRingTouchController->HandleTouchMove(data, m_cameraController->GetRenderCamera(), m_cameraController->GetNonFlattenedCameraPosition()))
        {
             m_cameraController->GetTouchController().Event_TouchMove(data);
        }
    }
    
    void InputController::Event_TouchUp(const AppInterface::TouchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        if (!m_poiRingTouchController->HandleTouchUp(data))
        {
            m_cameraController->GetTouchController().Event_TouchUp(data);
        }
    }
    
    void InputController::Event_Zoom(const AppInterface::ZoomData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_cameraController->GetTouchController().Event_Zoom(data);
    }
    
    void InputController::Event_Keyboard(const AppInterface::KeyboardData& data)
    {
        if (data.printable)
            Eegeo_TTY("Key Down: %c", data.keyCode);
        else
            Eegeo_TTY("Key Up: %c", data.keyCode);
    }
    
    void InputController::Event_TiltStart(const AppInterface::TiltData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_cameraController->GetTouchController().Event_TiltStart(data);
    }
    
    void InputController::Event_TiltEnd(const AppInterface::TiltData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_cameraController->GetTouchController().Event_TiltEnd(data);
    }
    
    void InputController::Event_Tilt(const AppInterface::TiltData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_cameraController->GetTouchController().Event_Tilt(data);
    }
    
    bool InputController::CanAcceptTouch() const
    {
        const bool worldIsInitialising = m_world->Initialising();// && m_loadingScreen != nullptr;
        const bool userInteractionEnabled = m_userInteractionModel->IsEnabled();
        const bool lockedCameraStepsCompleted = m_initialExperienceModel->LockedCameraStepsCompleted();
        return !worldIsInitialising && lockedCameraStepsCompleted && userInteractionEnabled;
    }
}