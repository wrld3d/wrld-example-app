//  Copyright (c) 2014 eeGeo. All rights reserved.

#include "AppDisplayAvailableMessage.h"
#include "IAppMessageDispatcher.h"

namespace AppLifecycleMessages
{
	bool AppDisplayAvailableMessage::Handle(AppMessages::IAppMessageDispatcher& dispatcher) const
	{
		return dispatcher.HandleMessage(*this);
	}
}




