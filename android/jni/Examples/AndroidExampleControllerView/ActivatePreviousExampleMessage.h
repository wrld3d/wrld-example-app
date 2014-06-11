/*
 * ActivatePreviousExampleMessage.h
 */

#ifndef ACTIVATEPREVIOUSEXAMPLEMESSAGE_H_
#define ACTIVATEPREVIOUSEXAMPLEMESSAGE_H_

#include "AndroidExampleControllerView.h"
#include "IAndroidExampleMessage.h"

namespace Examples
{
class ActivatePreviousExampleMessage : public AndroidExampleMessage<AndroidExampleControllerView>
{
public:
	ActivatePreviousExampleMessage(Examples::AndroidExampleControllerView* pExample);

	virtual bool Handle(AndroidExampleControllerView& dispatcher) const;
};
}

#endif /* ACTIVATEPREVIOUSEXAMPLEMESSAGE_H_ */
