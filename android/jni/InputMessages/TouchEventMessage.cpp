// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
