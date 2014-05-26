//
//  WebRequestExample.h
//  ExampleApp
//
//  Created by eeGeo on 30/04/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__WebRequestExample__
#define __ExampleApp__WebRequestExample__

#include "IExample.h"

#include "IWebLoadRequestFactory.h"
#include "WebLoadRequestCompletionCallback.h"
#include "IWebLoadRequest.h"

namespace Examples
{
    class WebRequestExample : public IExample
    {
    private:
        Eegeo::Web::IWebLoadRequestFactory& webRequestFactory;
        
    public:
        WebRequestExample(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory);
        
        static std::string GetName() { return "WebRequestExample"; }
        std::string Name() const { return GetName(); }
        
        void Start();
        void Update(float dt) {}
        void Draw() {}
        void Suspend() {}
    };
}


#endif /* defined(__ExampleApp__WebRequestExample__) */
