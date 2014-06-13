// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
