//
//  AndroidRouteMatchingExampleViewFactory.cpp
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "AndroidRouteMatchingExampleViewFactory.h"
#include "AndroidRouteMatchingExampleView.h"

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
    return Eegeo_NEW(AndroidRouteMatchingExampleView)(m_nativeState, m_messageQueue);
}
