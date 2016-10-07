// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IAndroidInputHandler.h"
#include <memory>
#include "AndroidInputProcessor.h"
#include "IAndroidInputHandler.h"
#include "IInputController.h"

namespace ExampleApp
{
	class InputController;
}

class AppInputDelegate : public Eegeo::Android::Input::IAndroidInputHandler, protected Eegeo::NonCopyable
{
public:
    AppInputDelegate(const std::shared_ptr<ExampleApp::IInputController>& inputController,
    		 	 	 const std::shared_ptr<Eegeo::Android::Input::AndroidInputProcessor>& inputProcessor,
					 const std::shared_ptr<Eegeo::Android::Input::IAndroidInputHandler>& inputHandler);
    ~AppInputDelegate();

    void HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event);
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
 	const std::shared_ptr<Eegeo::Android::Input::AndroidInputProcessor> m_inputProcessor;
	const std::shared_ptr<Eegeo::Android::Input::IAndroidInputHandler> m_inputHandler;
};


