//
//  IRouteMatchingView.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef ExampleApp_IRouteMatchingView_h
#define ExampleApp_IRouteMatchingView_h

#include "Types.h"
#include "IUIActionHandler.h"

namespace Examples
{
    class IRouteMatchingView
    {
    public:
        virtual ~IRouteMatchingView() { } 
        
        virtual void AddMatchingToggledHandler(IUIActionHandler& handler)=0;
        
        virtual void RemoveMatchingToggledHandler(IUIActionHandler& handler)=0;
    };
}

#endif
