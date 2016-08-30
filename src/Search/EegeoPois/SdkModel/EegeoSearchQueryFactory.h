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
#include "ApplicationConfiguration.h"
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
                    std::shared_ptr<Eegeo::Web::IWebLoadRequestFactory> m_webRequestFactory;
                    std::shared_ptr<Eegeo::Helpers::UrlHelpers::IUrlEncoder> m_urlEncoder;
                    std::shared_ptr<const Eegeo::Resources::Interiors::InteriorInteractionModel> m_interiorInteractionModel;
                    const std::string m_serviceUrl;
                public:
                    EegeoSearchQueryFactory(const std::shared_ptr<Eegeo::Web::IWebLoadRequestFactory>& webRequestFactory,
                                            const std::shared_ptr<Eegeo::Helpers::UrlHelpers::IUrlEncoder>& urlEncoder,
                                            const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel,
                                            const std::shared_ptr<ExampleApp::ApplicationConfig::ApplicationConfiguration>& config);
                    
                    ~EegeoSearchQueryFactory();
                    
                    IEegeoSearchQuery* CreateEegeoSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                         Eegeo::Helpers::ICallback0& completionCallback);
                    
                private:
                    const std::string m_apiKey;
                };
            }
        }
    }
}
