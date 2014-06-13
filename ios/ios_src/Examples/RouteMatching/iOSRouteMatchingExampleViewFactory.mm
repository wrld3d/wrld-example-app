// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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

IRouteMatchingExampleView* iOSRouteMatchingExampleViewFactory::CreateRouteMatchingExampleView() const
{
	return Eegeo_NEW(iOSRouteMatchingExampleView)(m_pView);
}
