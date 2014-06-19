// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__iOSRouteMatchingExampleViewFactory__
#define __ExampleApp__iOSRouteMatchingExampleViewFactory__

#include "Types.h"
#include "IRouteMatchingExampleViewFactory.h"
#import <UIKit/UIKit.h>

namespace Examples
{
class iOSRouteMatchingExampleViewFactory : public IRouteMatchingExampleViewFactory, private Eegeo::NonCopyable
{
	UIView* m_pView;

public:
	iOSRouteMatchingExampleViewFactory(UIView* pView);

	virtual ~iOSRouteMatchingExampleViewFactory();

	virtual IRouteMatchingExampleView* CreateRouteMatchingExampleView() const;
};
}

#endif /* defined(__ExampleApp__iOSRouteMatchingExampleViewFactory__) */
