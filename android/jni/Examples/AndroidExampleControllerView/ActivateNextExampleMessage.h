/*
 * ActivateNextExampleMessage.h
 */

#ifndef ACTIVATENEXTEXAMPLEMESSAGE_H_
#define ACTIVATENEXTEXAMPLEMESSAGE_H_

#include "AndroidExampleControllerView.h"
#include "IAndroidExampleMessage.h"

namespace Examples
{
	class ActivateNextExampleMessage : public AndroidExampleMessage<AndroidExampleControllerView>
	{
	public:
		ActivateNextExampleMessage(Examples::AndroidExampleControllerView* pExample);

        virtual bool Handle(AndroidExampleControllerView& dispatcher) const;
	};
}


#endif /* ACTIVATENEXTEXAMPLEMESSAGE_H_ */
