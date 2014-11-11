// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"

#ifdef EEGEO_DROID
	#define EEGEO_USE_CONCURRENT_MESSAGE_BUS
#endif

#ifdef EEGEO_USE_CONCURRENT_MESSAGE_BUS
	#include "MPMCMessageBus.h"
#else
	#include "ImmediateMessageBus.h"
#endif

namespace ExampleApp
{
    namespace ExampleAppMessaging
    {
#ifdef EEGEO_USE_CONCURRENT_MESSAGE_BUS
    	template <typename TMessageCatalog>
    	class MessageBus : public MPMCMessageBus<TMessageCatalog> { };
#else
    	template <typename TMessageCatalog>
    	class MessageBus : public ImmediateMessageBus<TMessageCatalog> { };
#endif
    }
}
