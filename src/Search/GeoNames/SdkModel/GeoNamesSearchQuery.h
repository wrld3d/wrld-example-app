// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "Types.h"
#include "IGeoNamesSearchQuery.h"
#include "Web.h"
#include "SearchQuery.h"
#include "WebLoadRequestCompletionCallback.h"
#include "UrlHelpers.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                class GeoNamesSearchQuery : public IGeoNamesSearchQuery, private Eegeo::NonCopyable
                {
                    Eegeo::Helpers::ICallback0& m_completionCallback;
                    std::string m_responseString;
                    bool m_isSuccess;
                    Eegeo::Web::TWebLoadRequestCompletionCallback<GeoNamesSearchQuery> m_webRequestCompleteCallback;
                    Eegeo::Web::IWebLoadRequest* m_pWebLoadRequest;
                    
                public:
                    GeoNamesSearchQuery(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                        Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                        const Search::SdkModel::SearchQuery& query,
                                        Eegeo::Helpers::ICallback0& completionCallback,
                                        const std::string& geoNamesUserName);
                    
                    ~GeoNamesSearchQuery();
                    
                    void Cancel();
                    
                    bool IsSucceeded();
                    
                    const std::string& ResponseString();
                    
                private:
                    void OnWebResponseReceived(Eegeo::Web::IWebResponse& webResponse);
                };
            }
        }
    }
}
