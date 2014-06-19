// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidRouteMatchingExampleViewFactory.h"
#include "AndroidRouteMatchingExampleView.h"

using namespace Examples;

AndroidRouteMatchingExampleViewFactory::AndroidRouteMatchingExampleViewFactory(
    AndroidNativeState& nativeState)
	: m_nativeState(nativeState)
{

}

AndroidRouteMatchingExampleViewFactory::~AndroidRouteMatchingExampleViewFactory()
{

}

IRouteMatchingExampleView* AndroidRouteMatchingExampleViewFactory::CreateRouteMatchingExampleView() const
{
	return Eegeo_NEW(AndroidRouteMatchingExampleView)(m_nativeState);
}
