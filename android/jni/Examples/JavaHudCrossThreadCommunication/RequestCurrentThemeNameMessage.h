/*
 * RequestCurrentThemeNameMessage.h
 */

#ifndef REQUESTCURRENTTHEMENAMEMESSAGE_H_
#define REQUESTCURRENTTHEMENAMEMESSAGE_H_

#include "JavaHudCrossThreadCommunicationExample.h"
#include "IAndroidExampleMessage.h"

namespace Examples
{
	class RequestCurrentThemeNameMessage : public AndroidExampleMessage<JavaHudCrossThreadCommunicationExample>
	{
	public:
		RequestCurrentThemeNameMessage(JavaHudCrossThreadCommunicationExample* pExample);

        virtual bool Handle(JavaHudCrossThreadCommunicationExample& dispatcher) const;
	};
}



#endif /* REQUESTCURRENTTHEMENAMEMESSAGE_H_ */
