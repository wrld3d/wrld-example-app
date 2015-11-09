// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MobileExampleApp.h"
#include "IWindowsInputHandler.h"

class AppInputDelegate : public Eegeo::Windows::Input::IWindowsInputHandler, protected Eegeo::NonCopyable
{
public:
    AppInputDelegate(ExampleApp::MobileExampleApp& exampleApp);
    ~AppInputDelegate();

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
    ExampleApp::MobileExampleApp& m_exampleApp;
};


