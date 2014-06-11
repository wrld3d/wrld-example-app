//
//  iOSRouteSimulationExampleViewFactory.cpp
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

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
