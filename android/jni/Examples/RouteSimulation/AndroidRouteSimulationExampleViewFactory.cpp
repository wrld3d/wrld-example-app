//
//  AndroidRouteSimulationExampleViewFactory.cpp
//

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
