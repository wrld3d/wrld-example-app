// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
