//
//  IUIActionHandler.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef ExampleApp_IUIActionHandler_h
#define ExampleApp_IUIActionHandler_h

namespace Examples
{
    class IUIActionHandler
    {
    public:
    	virtual ~IUIActionHandler() {}
        virtual void operator()() = 0;
    };
}

#endif
