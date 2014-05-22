//  Copyright (c) 2014 eeGeo. All rights reserved.

#include "AppPauseMessage.h"
#include "IAppMessageDispatcher.h"

namespace AppLifecycleMessages
{
	bool AppPauseMessage::Handle(AppMessages::IAppMessageDispatcher& dispatcher) const
	{
		return dispatcher.HandleMessage(*this);
	}
}





