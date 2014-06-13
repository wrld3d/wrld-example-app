// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidExampleProxy.h"

using namespace Examples;

AndroidExampleProxy::AndroidExampleProxy(Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue)
	: m_messageQueue(messageQueue)
{

}

void AndroidExampleProxy::SendMessage(IAndroidExampleMessage* pMessage)
{
	m_messageQueue.Enqueue(pMessage);
}
