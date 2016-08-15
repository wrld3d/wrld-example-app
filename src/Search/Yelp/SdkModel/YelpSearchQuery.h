// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "IYelpSearchQuery.h"
#include "Types.h"
#include "SearchQuery.h"
#include "ICallback.h"
#include "Yelp.h"
#include "IWebLoadRequestFactory.h"
#include "WebLoadRequestCompletionCallback.h"



namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class YelpSearchQuery : public SdkModel::IYelpSearchQuery, private Eegeo::NonCopyable
                {
                public:
                    YelpSearchQuery(
                        const std::string& requestUrl,
                        Eegeo::Helpers::ICallback0& completionCallback,
                        Eegeo::Web::IWebLoadRequestFactory& webRequestFactory);

                    ~YelpSearchQuery();

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
                    Eegeo::Web::TWebLoadRequestCompletionCallback<YelpSearchQuery> m_webRequestCompleteCallback;
                };
            }
        }
    }
}
