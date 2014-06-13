// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef APPPAUSEMESSAGE_H_
#define APPPAUSEMESSAGE_H_

#include "AppMessages.h"
#include "IAppMessage.h"

namespace AppLifecycleMessages
{
class AppPauseMessage : public AppMessages::IAppMessage
{
public:
	bool Handle(AppMessages::IAppMessageDispatcher& dispatcher) const;
};
}

#endif
