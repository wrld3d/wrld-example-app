// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
