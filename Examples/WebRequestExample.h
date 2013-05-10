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
    class WebRequestExample : public IExample, public Eegeo::Web::TWebLoadRequestCompletionCallback<WebRequestExample>
    {
    private:
        Eegeo::Web::IWebLoadRequestFactory& webRequestFactory;
        
    public:
        WebRequestExample(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory);
        
        void Start();
        void Update() {}
        void Draw() {}
        void Suspend() {}
        
        void RequestComplete(Eegeo::Web::IWebLoadRequest& webLoadRequest);
    };
}


#endif /* defined(__ExampleApp__WebRequestExample__) */
