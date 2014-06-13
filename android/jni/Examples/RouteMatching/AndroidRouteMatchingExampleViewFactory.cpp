// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidRouteMatchingExampleViewFactory.h"
#include "AndroidRouteMatchingExampleView.h"
#include "AndroidRouteMatchingProxy.h"

using namespace Examples;

AndroidRouteMatchingExampleViewFactory::AndroidRouteMatchingExampleViewFactory(
    AndroidNativeState& nativeState,
    Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue)
	: m_nativeState(nativeState)
	, m_messageQueue(messageQueue)
{

}

AndroidRouteMatchingExampleViewFactory::~AndroidRouteMatchingExampleViewFactory()
{

}

IRouteMatchingExampleView* AndroidRouteMatchingExampleViewFactory::CreateRouteMatchingExampleView() const
{
	AndroidRouteMatchingProxy* pProxy = Eegeo_NEW(AndroidRouteMatchingProxy)(m_messageQueue);

	return Eegeo_NEW(AndroidRouteMatchingExampleView)(m_nativeState, pProxy);
}
