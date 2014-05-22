//  Copyright (c) 2014 eeGeo. All rights reserved.

#ifndef IINPUTMESSAGEDISPATCHER_H_
#define IINPUTMESSAGEDISPATCHER_H_

#include "InputMessages.h"

namespace InputMessages
{
	class IInputMessageDispatcher
	{
	public:
		virtual ~IInputMessageDispatcher() {};
		virtual bool HandleMessage(const TouchEventMessage& message) = 0;
	};
}

#endif
