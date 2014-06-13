// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AppDisplayAvailableMessage.h"
#include "IAppMessageDispatcher.h"

namespace AppLifecycleMessages
{
bool AppDisplayAvailableMessage::Handle(AppMessages::IAppMessageDispatcher& dispatcher) const
{
	return dispatcher.HandleMessage(*this);
}
}




