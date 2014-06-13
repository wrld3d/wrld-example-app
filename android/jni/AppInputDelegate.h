// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef APPINPUTDELEGATE_H_
#define APPINPUTDELEGATE_H_

#include "Types.h"
#include "ExampleApp.h"
#include "IAndroidInputHandler.h"

class AppInputDelegate : public Eegeo::Android::Input::IAndroidInputHandler, protected Eegeo::NonCopyable
{
public:
	AppInputDelegate(ExampleApp& exampleApp);
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
	ExampleApp& m_exampleApp;
};

#endif
