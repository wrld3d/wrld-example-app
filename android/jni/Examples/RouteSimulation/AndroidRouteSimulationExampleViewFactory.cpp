// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidRouteSimulationExampleViewFactory.h"
#include "AndroidRouteSimulationExampleView.h"
#include "AndroidRouteSimulationProxy.h"

using namespace Examples;

AndroidRouteSimulationExampleViewFactory::AndroidRouteSimulationExampleViewFactory(
    AndroidNativeState& nativeState,
    Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue)
	: m_nativeState(nativeState)
	, m_messageQueue(messageQueue)
{

}

AndroidRouteSimulationExampleViewFactory::~AndroidRouteSimulationExampleViewFactory()
{

}

IRouteSimulationExampleView* AndroidRouteSimulationExampleViewFactory::CreateRouteSimulationExampleView() const
{
	AndroidRouteSimulationProxy* pProxy = Eegeo_NEW(AndroidRouteSimulationProxy)(m_messageQueue);

	return Eegeo_NEW(AndroidRouteSimulationExampleView)(m_nativeState, pProxy, false);
}
