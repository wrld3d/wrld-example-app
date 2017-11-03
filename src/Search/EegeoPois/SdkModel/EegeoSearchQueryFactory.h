// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "Types.h"
#include "IEegeoSearchQueryFactory.h"
#include "IEegeoSearchQuery.h"
#include "Web.h"
#include "UrlHelpers.h"
#include "Interiors.h"
#include "IAppModeModel.h"
#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoSearchQueryFactory : public IEegeoSearchQueryFactory, private Eegeo::NonCopyable
                {
                    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                    Eegeo::Helpers::UrlHelpers::IUrlEncoder& m_urlEncoder;
                    const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                    const std::string m_serviceUrl;
                public:
                    EegeoSearchQueryFactory(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                            Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                            const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                            const std::string& serviceUrl,
                                            const Eegeo::Web::ApiTokenModel& apiTokenModel);
                    
                    ~EegeoSearchQueryFactory();
                    
                    IEegeoSearchQuery* CreateEegeoSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                         Eegeo::Helpers::ICallback0& completionCallback);
                    
                private:
                    const Eegeo::Web::ApiTokenModel& m_apiTokenModel;
                };
            }
        }
    }
}
