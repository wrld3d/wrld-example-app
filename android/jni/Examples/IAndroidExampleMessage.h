/*
 * IAndroidExampleMessage.h
 */

#ifndef IANDROIDEXAMPLEMESSAGE_H_
#define IANDROIDEXAMPLEMESSAGE_H_

#include "IMessage.h"

namespace Examples
{
class IAndroidExampleMessage
{
public:
	virtual ~IAndroidExampleMessage() { }

	virtual void Handle()=0;

protected:
	IAndroidExampleMessage() {}
};

template <typename THandler>
class AndroidExampleMessage : public IAndroidExampleMessage, public Eegeo::Messaging::IMessage<THandler>
{
	THandler* m_pHandler;
public:
	AndroidExampleMessage(THandler* pHandler)
		: m_pHandler(pHandler)
	{
		Eegeo_ASSERT(pHandler != NULL, "AndroidExampleMessage handler pointer must be non-null.\n");
	}

	void Handle()
	{
		Eegeo::Messaging::IMessage<THandler>* pThis = this;
		pThis->Handle(*m_pHandler);
	}
};
}

#endif /* IANDROIDEXAMPLEMESSAGE_H_ */
