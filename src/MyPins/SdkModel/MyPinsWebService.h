// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WebLoadRequestCompletionCallback.h"
#include "MyPins.h"
#include "Search.h"
#include "Helpers.h"
#include "Web.h"
#include "ApplicationConfiguration.h"
#include <string>

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinsWebService : private Eegeo::NonCopyable
            {
            public:
                MyPinsWebService(
                                 const std::shared_ptr<ApplicationConfig::ApplicationConfiguration>& appConfig,
                                 const std::shared_ptr<Eegeo::Web::IWebLoadRequestFactory>& webLoadRequestFactory,
                                 const std::shared_ptr<Eegeo::Helpers::IFileIO>& fileIO);
                
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
                const std::shared_ptr<Eegeo::Web::IWebLoadRequestFactory>& m_webLoadRequestFactory;
                const std::shared_ptr<Eegeo::Helpers::IFileIO>& m_fileIO;
                Eegeo::Web::TWebLoadRequestCompletionCallback<MyPinsWebService> m_webRequestCompleteCallback;
            };
        }
    }
}

