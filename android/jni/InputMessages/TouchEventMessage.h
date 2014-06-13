// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef TOUCHEVENTMESSAGE_H_
#define TOUCHEVENTMESSAGE_H_

#include "AppMessages.h"
#include "IAppMessage.h"
#include "TouchEventType.h"
#include "TouchEventWrapper.h"

namespace InputMessages
{
class TouchEventMessage : public AppMessages::IAppMessage
{
public:
	TouchEventMessage(const Eegeo::Android::Input::TouchInputEvent& touchInputEvent);

	bool Handle(AppMessages::IAppMessageDispatcher& dispatcher) const;

	const Eegeo::Android::Input::TouchInputEvent& GetTouchInputEvent() const;

private:
	Eegeo::Android::Input::TouchInputEvent m_touchInputEvent;
};
}

#endif
