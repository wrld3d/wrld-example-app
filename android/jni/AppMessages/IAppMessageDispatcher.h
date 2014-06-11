//  Copyright (c) 2014 eeGeo. All rights reserved.

#ifndef IAPPMESSAGEDISPATCHER_H_
#define IAPPMESSAGEDISPATCHER_H_

#include "AppMessages.h"
#include "AppLifecycleMessages.h"
#include "InputMessages.h"

#include "IAppLifecycleMessageDispatcher.h"
#include "IInputMessageDispatcher.h"

namespace AppMessages
{
class IAppMessageDispatcher
{
public:
	virtual ~IAppMessageDispatcher() {};

	virtual bool HandleMessage(const AppLifecycleMessages::AppPauseMessage& message) = 0;
	virtual bool HandleMessage(const AppLifecycleMessages::AppDisplayAvailableMessage& message) = 0;
	virtual bool HandleMessage(const InputMessages::TouchEventMessage& message) = 0;
};
}

#endif
