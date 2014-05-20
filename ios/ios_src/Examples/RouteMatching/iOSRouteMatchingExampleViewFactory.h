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
