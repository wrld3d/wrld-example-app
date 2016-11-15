// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Yelp.h"
#include "Search.h"
#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"
#include "ICallback.h"

#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class YelpBusinessQuery : private Eegeo::NonCopyable
                {
                public:
                    YelpBusinessQuery(
                                      const std::string& requestUrl,
                                      Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& completionCallback,
                                      Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                      const YelpBusinessJsonParser& yelpBusinessParser);
                    
                    ~YelpBusinessQuery();
                    
                    void Dispatch();
                    
                    void Cancel();
                
                    
                private:
                    void HandleWebResponseComplete(Eegeo::Web::IWebResponse& webResponse);

                    Eegeo::Web::IWebLoadRequest* m_pWebLoadRequest;
                    Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& m_completionCallback;
                    const YelpBusinessJsonParser& m_yelpBusinessParser;
                    
                    bool m_dispatched;
                    
                    Eegeo::Web::TWebLoadRequestCompletionCallback<YelpBusinessQuery> m_webRequestCompleteCallback;
                };
            }
        }
    }
}
