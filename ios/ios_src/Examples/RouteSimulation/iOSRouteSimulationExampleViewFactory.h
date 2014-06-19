// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__iOSRouteSimulationExampleViewFactory__
#define __ExampleApp__iOSRouteSimulationExampleViewFactory__

#include "Types.h"
#include "IRouteSimulationExampleViewFactory.h"
#include "IRouteSimulationExampleView.h"
#import <UIKit/UIKit.h>

namespace Examples
{
class iOSRouteSimulationExampleViewFactory : public IRouteSimulationExampleViewFactory, private Eegeo::NonCopyable
{
	UIView* m_pView;

public:
	iOSRouteSimulationExampleViewFactory(UIView* pView);

	~iOSRouteSimulationExampleViewFactory();

	IRouteSimulationExampleView* CreateRouteSimulationExampleView() const;
};
}

#endif /* defined(__ExampleApp__iOSRouteSimulationExampleViewFactory__) */
