// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
