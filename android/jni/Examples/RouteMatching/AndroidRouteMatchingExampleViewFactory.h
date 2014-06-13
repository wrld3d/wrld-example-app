// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__AndroidRouteMatchingExampleViewFactory__
#define __ExampleApp__AndroidRouteMatchingExampleViewFactory__

#include "Types.h"
#include "IRouteMatchingExampleViewFactory.h"
#include "AndroidNativeState.h"
#include "MessageQueue.h"
#include "IAndroidExampleMessage.h"

namespace Examples
{
class AndroidRouteMatchingExampleViewFactory : public IRouteMatchingExampleViewFactory, private Eegeo::NonCopyable
{
	AndroidNativeState& m_nativeState;
	Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& m_messageQueue;

public:
	AndroidRouteMatchingExampleViewFactory(
	    AndroidNativeState& androidNativeState,
	    Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue);

	virtual ~AndroidRouteMatchingExampleViewFactory();

	virtual IRouteMatchingExampleView* CreateRouteMatchingExampleView() const;
};
}

#endif /* defined(__ExampleApp__AndroidRouteMatchingExampleViewFactory__) */
