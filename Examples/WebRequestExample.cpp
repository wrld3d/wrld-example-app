//
//  WebRequestExample.cpp
//  ExampleApp
//
//  Created by eeGeo on 30/04/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#include "WebRequestExample.h"
#include <map>
#include <string>

using namespace Eegeo::Web;

namespace {
    class ExternalHandlerType_NotPartOfPublicAPI : public IWebLoadRequestCompletionCallback
    {
        void operator()(IWebLoadRequest& webLoadRequest)
        {
            int* userData = (int*)webLoadRequest.GetUserData();
            const std::string& url = webLoadRequest.GetUrl();
            size_t responseBodySize = webLoadRequest.GetResourceData().size();
            
            Eegeo_TTY("Finished Https POST of %s in a non member function of calling type, with user data %d - resource size of %ld\n",
                      url.c_str(), *userData, responseBodySize);
            
            delete userData;
            
            Eegeo_TTY("\nIs our fake token a valid key? Response was: %s\n", &webLoadRequest.GetResourceData()[0]);
        }
    };
    ExternalHandlerType_NotPartOfPublicAPI externalHandler;
}

namespace Examples
{
    WebRequestExample::WebRequestExample(IWebLoadRequestFactory& webRequestFactory)
    :TWebLoadRequestCompletionCallback<WebRequestExample>(this, &WebRequestExample::RequestComplete)
    ,webRequestFactory(webRequestFactory)
    {
    }
    
    void WebRequestExample::Start()
    {
        Eegeo_TTY("Making 3 Http GETs with integer labels as user data using a member as the handler...\n");
        webRequestFactory.CreateGet("http://appstore.eegeo.com", *this, new int(1))->Load();
        webRequestFactory.CreateGet("http://appstore.eegeo.com", *this, new int(2))->Load();
        webRequestFactory.CreateGet("http://wikipedia.org", *this, new int(3))->Load();
        
        std::map<std::string, std::string> postData;
        postData["token"] = "123456789";
        Eegeo_TTY("Making Https POST to Eegeo appstore with invalid key (123456789), with integer labels as user data using a non-member as the handler...\n");
        webRequestFactory.CreatePost("https://appstore.eegeo.com/validate", externalHandler, new int(5678), postData)->Load();
    }

    void WebRequestExample::RequestComplete(IWebLoadRequest& webLoadRequest)
    {
        int* userData = (int*)webLoadRequest.GetUserData();
        const std::string& url = webLoadRequest.GetUrl();
        size_t responseBodySize = webLoadRequest.GetResourceData().size();
        
        Eegeo_TTY("Finished Http GET of %s in a member function of calling type, with user data %d - resource size of %ld\n",
                  url.c_str(), *userData, responseBodySize);
        
        delete userData;
    }
}
