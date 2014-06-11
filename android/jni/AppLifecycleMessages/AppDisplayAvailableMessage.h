//  Copyright (c) 2014 eeGeo. All rights reserved.

#ifndef APPDISPLAYAVAILABLEMESSAGE_H_
#define APPDISPLAYAVAILABLEMESSAGE_H_

#include "AppMessages.h"
#include "IAppMessage.h"

namespace AppLifecycleMessages
{
class AppDisplayAvailableMessage : public AppMessages::IAppMessage
{
public:
	bool Handle(AppMessages::IAppMessageDispatcher& dispatcher) const;
};
}

#endif
