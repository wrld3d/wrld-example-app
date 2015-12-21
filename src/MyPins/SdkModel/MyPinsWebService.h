// Copyright (c) 2015 eeGeo. All rights reserved.

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
                                 const std::string& webServiceBaseUrl,
                                 const std::string& webServiceAuthToken,
                                 Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory,
                                 Eegeo::Helpers::IFileIO& fileIO);
                
                void SubmitSearchResultPin(
                                           const MyPinModel& pinModel,
                                           const Search::SdkModel::SearchResultModel& searchResult);
                
                void SubmitUserCreatedPin(
                                          const MyPinModel& pinModel,
                                          const std::string& imagePath);
                
            private:
                
                void WebRequestCompleteCallback(Eegeo::Web::IWebResponse& webResponse);
                
                const std::string m_url;
                const std::string m_authHeader;
                Eegeo::Web::IWebLoadRequestFactory& m_webLoadRequestFactory;
                Eegeo::Helpers::IFileIO& m_fileIO;
                Eegeo::Web::TWebLoadRequestCompletionCallback<MyPinsWebService> m_webRequestCompleteCallback;
            };
        }
    }
}

