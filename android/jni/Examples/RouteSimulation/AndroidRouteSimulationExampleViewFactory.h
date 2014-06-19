// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__AndroidRouteSimulationExampleViewFactory__
#define __ExampleApp__AndroidRouteSimulationExampleViewFactory__

#include "Types.h"
#include "IRouteSimulationExampleViewFactory.h"
#include "AndroidNativeState.h"

namespace Examples
{
class AndroidRouteSimulationExampleViewFactory : public IRouteSimulationExampleViewFactory, private Eegeo::NonCopyable
{
	AndroidNativeState& m_nativeState;

public:
	AndroidRouteSimulationExampleViewFactory(AndroidNativeState& androidNativeState);

	virtual ~AndroidRouteSimulationExampleViewFactory();

	virtual IRouteSimulationExampleView* CreateRouteSimulationExampleView() const;
};
}

#endif /* defined(__ExampleApp__iOSRouteSimulationExampleViewFactory__) */
