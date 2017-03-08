// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "Types.h"
#include "IEegeoSearchQuery.h"
#include "Web.h"
#include "SearchQuery.h"
#include "WebLoadRequestCompletionCallback.h"
#include "UrlHelpers.h"
#include "InteriorId.h"

#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoSearchQuery : public IEegeoSearchQuery, private Eegeo::NonCopyable
                {
                    Eegeo::Helpers::ICallback0& m_completionCallback;
                    std::string m_responseString;
                    bool m_isSuccess;
                    Eegeo::Web::TWebLoadRequestCompletionCallback<EegeoSearchQuery> m_webRequestCompleteCallback;
                    Eegeo::Web::IWebLoadRequest* m_pWebLoadRequest;
                public:
                    EegeoSearchQuery(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                     Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                     const Search::SdkModel::SearchQuery& query,
                                     const std::string& serviceUrl,
                                     const Eegeo::Web::ApiTokenModel& apiTokenModel,
                                     const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                     int interiorFloorIndex,
                                     Eegeo::Helpers::ICallback0& completionCallback);
                    
                    ~EegeoSearchQuery();
                    
                    void Cancel();
                    
                    bool IsSucceeded();
                    
                    const std::string& ResponseString();
                    
                private:
                    void OnWebResponseReceived(Eegeo::Web::IWebResponse& webResponse);
                    const Eegeo::Web::ApiTokenModel& m_apiTokenModel;
                };
            }
        }
    }
}
