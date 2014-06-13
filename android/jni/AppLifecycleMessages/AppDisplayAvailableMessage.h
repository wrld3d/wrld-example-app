// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
