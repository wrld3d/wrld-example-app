//  Copyright (c) 2014 eeGeo. All rights reserved.

#include "TouchEventMessage.h"
#include "IAppMessageDispatcher.h"

namespace InputMessages
{
TouchEventMessage::TouchEventMessage(const Eegeo::Android::Input::TouchInputEvent& touchInputEvent)
	: m_touchInputEvent(touchInputEvent)
{
}

const Eegeo::Android::Input::TouchInputEvent& TouchEventMessage::GetTouchInputEvent() const
{
	return m_touchInputEvent;
}

bool TouchEventMessage::Handle(AppMessages::IAppMessageDispatcher& dispatcher) const
{
	return dispatcher.HandleMessage(*this);
}
}
