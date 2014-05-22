//  Copyright (c) 2014 eeGeo. All rights reserved.

#ifndef IAPPLIFECYCLEMESSAGEDISPATCHER_H_
#define IAPPLIFECYCLEMESSAGEDISPATCHER_H_

#include "AppLifecycleMessages.h"

namespace AppLifecycleMessages
{
	class IAppLifecycleMessageDispatcher
	{
	public:
		virtual ~IAppLifecycleMessageDispatcher() {};
		virtual bool HandleMessage(const AppPauseMessage& message) = 0;
		virtual bool HandleMessage(const AppDisplayAvailableMessage& message) = 0;
	};
}

#endif /* IAPPLIFECYCLEMESSAGEDISPATCHER_H_ */
