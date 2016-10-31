// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "FindDirectionQuery.h"
#include "IWebLoadRequestFactory.h"
#include "WebLoadRequestCompletionCallback.h"



namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class FindDirectionHttpRequest :  private Eegeo::NonCopyable
            {
                
            public:
                FindDirectionHttpRequest(
                                const std::string& requestUrl,
                                Eegeo::Helpers::ICallback0& completionCallback,
                                Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                         Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                         const FindDirectionQuery& query,
                                         const std::string& eegeoApiKey);
                
                ~FindDirectionHttpRequest();
                
                void Dispatch();
                
                void Cancel();
                
                bool IsSucceeded();
                
                const std::string& ResponseString();
            
            private:
                
                void HandleWebResponseComplete(Eegeo::Web::IWebResponse& webResponse);
                
                Eegeo::Web::IWebLoadRequest* m_pWebLoadRequest;
                Eegeo::Helpers::ICallback0& m_completionCallback;
                std::string m_responseString;
                
                bool m_dispatched;
                bool m_isSuccess;
                
                Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                Eegeo::Web::TWebLoadRequestCompletionCallback<FindDirectionHttpRequest> m_webRequestCompleteCallback;
            };
        }
    }
}