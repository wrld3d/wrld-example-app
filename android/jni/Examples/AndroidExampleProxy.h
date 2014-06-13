// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef ANDROIDEXAMPLEPROXY_H_
#define ANDROIDEXAMPLEPROXY_H_

#include "MessageQueue.h"
#include "IAndroidExampleMessage.h"

namespace Examples
{
class AndroidExampleProxy
{
	Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& m_messageQueue;
protected:
	void SendMessage(IAndroidExampleMessage* pMessage);

	AndroidExampleProxy(Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue);
};
}

#endif /* ANDROIDEXAMPLEPROXY_H_ */
