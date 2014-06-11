//  Copyright (c) 2014 eeGeo. All rights reserved.

#ifndef IAPPTOJAVAMESSAGE_H_
#define IAPPTOJAVAMESSAGE_H_

#include "IMessage.h"
#include "IAppToJavaMessageDispatcher.h"

namespace AppMessages
{
namespace AppToJava
{
class IAppToJavaMessage : public Eegeo::Messaging::IMessage<IAppToJavaMessageDispatcher>
{
public:
	virtual ~IAppToJavaMessage() { };
};
}
}



#endif /* IAPPTOJAVAMESSAGE_H_ */
