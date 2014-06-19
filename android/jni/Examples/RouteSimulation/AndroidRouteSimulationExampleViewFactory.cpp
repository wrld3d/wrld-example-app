// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidRouteSimulationExampleViewFactory.h"
#include "AndroidRouteSimulationExampleView.h"

using namespace Examples;

AndroidRouteSimulationExampleViewFactory::AndroidRouteSimulationExampleViewFactory(
    AndroidNativeState& nativeState)
	: m_nativeState(nativeState)
{

}

AndroidRouteSimulationExampleViewFactory::~AndroidRouteSimulationExampleViewFactory()
{

}

IRouteSimulationExampleView* AndroidRouteSimulationExampleViewFactory::CreateRouteSimulationExampleView() const
{
	return Eegeo_NEW(AndroidRouteSimulationExampleView)(m_nativeState, false);
}
