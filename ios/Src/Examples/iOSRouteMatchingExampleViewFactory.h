//
//  iOSRouteMatchingExampleViewFactory.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__iOSRouteMatchingExampleViewFactory__
#define __ExampleApp__iOSRouteMatchingExampleViewFactory__

#include "Types.h"
#include "IRouteMatchingViewFactory.h"
#import <UIKit/UIKit.h>

namespace Examples
{
    class iOSRouteMatchingExampleViewFactory : public IRouteMatchingViewFactory, private Eegeo::NonCopyable
    {
        UIView* m_pView;
        
    public:
        iOSRouteMatchingExampleViewFactory(UIView* pView);
        
        virtual ~iOSRouteMatchingExampleViewFactory();
        
        virtual IRouteMatchingView* CreateRouteMatchingView() const;
    };
}

#endif /* defined(__ExampleApp__iOSRouteMatchingExampleViewFactory__) */
