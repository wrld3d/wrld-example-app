// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "Types.h"
#include "IEegeoSearchQuery.h"
#include "Web.h"
#include "SearchQuery.h"
#include "Interiors.h"
#include "WebLoadRequestCompletionCallback.h"
#include "UrlHelpers.h"

#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoInteriorSearchQuery : public IEegeoSearchQuery, private Eegeo::NonCopyable
                {
                    Eegeo::Helpers::ICallback0& m_completionCallback;
                    std::string m_responseString;
                    bool m_isSuccess;
                    const Eegeo::Resources::Interiors::InteriorId& m_interiorId;
                    int m_floorIdx;
                    Eegeo::Web::TWebLoadRequestCompletionCallback<EegeoInteriorSearchQuery> m_webRequestCompleteCallback;
                    Eegeo::Web::IWebLoadRequest* m_pWebLoadRequest;
                public:
                    EegeoInteriorSearchQuery(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                         Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                         const Search::SdkModel::SearchQuery& query,
                                         const std::string& serviceUrl,
                                         const Eegeo::Web::ApiTokenModel& apiTokenModel,
                                         const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                         int floorIdx,
                                         Eegeo::Helpers::ICallback0& completionCallback);
                    
                    ~EegeoInteriorSearchQuery();
                    
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
