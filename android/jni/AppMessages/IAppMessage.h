//  Copyright (c) 2014 eeGeo. All rights reserved.

#ifndef IAPPMESSAGE_H_
#define IAPPMESSAGE_H_

#include "IMessage.h"
#include "IAppMessageDispatcher.h"

namespace AppMessages
{
	class IAppMessage : public Eegeo::Messaging::IMessage<IAppMessageDispatcher>
	{
	};
}

#endif
