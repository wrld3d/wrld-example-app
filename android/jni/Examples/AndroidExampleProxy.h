/*
 * AndroidExampleProxy.h
 */

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
