//
//  iOSRouteMatchingExampleViewFactory.cpp
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "iOSRouteMatchingExampleViewFactory.h"
#include "iOSRouteMatchingExampleView.h"

using namespace Examples;

iOSRouteMatchingExampleViewFactory::iOSRouteMatchingExampleViewFactory(UIView* pView)
: m_pView(pView)
{
    
}

iOSRouteMatchingExampleViewFactory::~iOSRouteMatchingExampleViewFactory()
{
    
}

IRouteMatchingView* iOSRouteMatchingExampleViewFactory::CreateRouteMatchingView() const
{
    return Eegeo_NEW(iOSRouteMatchingExampleView)(m_pView);
}
