// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MobileExampleApp.h"
#include "IWindowsInputHandler.h"
#include "WindowsInputProcessor.h"
#include "IInputController.h"
#include "MouseInputEvent.h"
#include "TouchScreenInputEvent.h"
#include "WindowsInput.h"

class AppInputDelegate : public Eegeo::Windows::Input::IWindowsInputHandler, protected Eegeo::NonCopyable
{
public:
    AppInputDelegate(const std::shared_ptr<ExampleApp::IInputController>& inputController,
                     const std::shared_ptr<Eegeo::Windows::Input::WindowsInputProcessor>& inputProcessor,
                     const std::shared_ptr<Eegeo::Windows::Input::IWindowsInputHandler>& inputHandle);
    ~AppInputDelegate();

    void HandleMouseInput(const Eegeo::Windows::Input::MouseInputEvent& event, float screenWidth, float screenHeight);
    void HandleMouseInput(const Eegeo::Windows::Input::KeyboardInputEvent& keyEvent);
    void HandleTouchScreenInput(const Eegeo::Windows::Input::TouchScreenInputEvent& event, float screenWidth, float screenHeight);
    void SetAllInputEventsToPointerUp(int x, int y);
    void SetTouchInputEventToPointerUp(int touchId);
    void PopAllTouchEvents();

    void Update(float dt);
    void SetViewportOffset(float x, float y);

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
    void Event_Zoom(const AppInterface::ZoomData& data);

    void Event_TiltStart(const AppInterface::TiltData& data);
    void Event_TiltEnd(const AppInterface::TiltData& data);
    void Event_Tilt(const AppInterface::TiltData& data);

    bool Event_KeyPress(const AppInterface::KeyboardData& data)
    {
        return false;
    }
    void AddKeyPressListener(Eegeo::UI::NativeInput::IKeyboardInputKeyPressedHandler* handler) { }
    bool RemoveKeyPressListener(Eegeo::UI::NativeInput::IKeyboardInputKeyPressedHandler* handler)
    {
        return false;
    }

private:
    const std::shared_ptr<ExampleApp::IInputController> m_inputController;
    const std::shared_ptr<Eegeo::Windows::Input::WindowsInputProcessor> m_inputProcessor;
    const std::shared_ptr<Eegeo::Windows::Input::IWindowsInputHandler> m_inputHandler;
};


