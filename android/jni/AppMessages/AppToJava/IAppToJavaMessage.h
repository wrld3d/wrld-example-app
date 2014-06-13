// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
