// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "iOSRouteSimulationExampleViewFactory.h"
#include "iOSRouteSimulationExampleView.h"

using namespace Examples;

iOSRouteSimulationExampleViewFactory::iOSRouteSimulationExampleViewFactory(UIView* pView)
	: m_pView(pView)
{

}

iOSRouteSimulationExampleViewFactory::~iOSRouteSimulationExampleViewFactory()
{

}

IRouteSimulationExampleView* iOSRouteSimulationExampleViewFactory::CreateRouteSimulationExampleView() const
{
	return Eegeo_NEW(iOSRouteSimulationExampleView)(m_pView);
}
