/*
 * AndroidExampleProxy.cpp
 */

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
