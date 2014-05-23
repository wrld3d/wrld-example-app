/*
 * ToggleRouteMatchingMessage.h
 */

#ifndef TOGGLEROUTEMATCHINGMESSAGE_H_
#define TOGGLEROUTEMATCHINGMESSAGE_H_

#include "AndroidRouteMatchingExampleView.h"
#include "IAndroidExampleMessage.h"

namespace Examples
{
	class ToggleRouteMatchingMessage : public AndroidExampleMessage<AndroidRouteMatchingExampleView>
	{
	public:
		ToggleRouteMatchingMessage(Examples::AndroidRouteMatchingExampleView* pExample);

        virtual bool Handle(AndroidRouteMatchingExampleView& dispatcher) const;
	};
}



#endif /* TOGGLEROUTEMATCHINGMESSAGE_H_ */
