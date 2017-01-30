// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WebLoadRequestCompletionCallback.h"
#include "MyPins.h"
#include "Search.h"
#include "Helpers.h"
#include "Web.h"
#include <string>

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinsWebService
            {
            public:
                MyPinsWebService(
                                 const std::string& myPinsWebServiceBaseUrl,
                                 const std::string& myPinsWebServiceAuthToken,
                                 const std::string& myPinsPoiSetId,
                                 Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory);
                
                void SubmitUserCreatedPin(
                                          const MyPinModel& pinModel);
                
            private:
                
                void WebRequestCompleteCallback(Eegeo::Web::IWebResponse& webResponse);
                const std::string CreatePinPostData(const MyPinModel& pinModel);
                const std::string CreatePoiServiceUrl();
                
                const std::string m_url;
                const std::string m_myPinsWebServiceAuthToken;
                const std::string m_myPinsPoiSetId;
                Eegeo::Web::IWebLoadRequestFactory& m_webLoadRequestFactory;
                Eegeo::Web::TWebLoadRequestCompletionCallback<MyPinsWebService> m_webRequestCompleteCallback;
            };
        }
    }
}

