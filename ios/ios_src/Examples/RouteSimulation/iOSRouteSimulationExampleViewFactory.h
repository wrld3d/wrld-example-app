//
//  iOSRouteSimulationExampleViewFactory.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

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
