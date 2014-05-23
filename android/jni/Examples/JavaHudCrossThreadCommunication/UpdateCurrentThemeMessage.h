/*
 * UpdateCurrentThemeMessage.h
 */

#ifndef UPDATECURRENTTHEMEMESSAGE_H_
#define UPDATECURRENTTHEMEMESSAGE_H_

#include "JavaHudCrossThreadCommunicationExample.h"
#include "IAndroidExampleMessage.h"

namespace Examples
{
	class UpdateCurrentThemeMessage : public AndroidExampleMessage<JavaHudCrossThreadCommunicationExample>
	{
		std::string m_themeName;
	public:
		UpdateCurrentThemeMessage(JavaHudCrossThreadCommunicationExample* pExample, const std::string& themeName);

        virtual bool Handle(JavaHudCrossThreadCommunicationExample& dispatcher) const;
	};
}

#endif /* UPDATECURRENTTHEMEMESSAGE_H_ */
