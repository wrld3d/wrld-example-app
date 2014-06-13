// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AppPauseMessage.h"
#include "IAppMessageDispatcher.h"

namespace AppLifecycleMessages
{
bool AppPauseMessage::Handle(AppMessages::IAppMessageDispatcher& dispatcher) const
{
	return dispatcher.HandleMessage(*this);
}
}





