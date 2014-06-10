//
//  AndroidRouteMatchingExampleViewFactory.cpp
//

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
