// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"

#include "Types.h"
#include "UrlHelpers.h"
#include "Web.h"
#include "EegeoPois.h"
#include "NetIncludes.h"
#include "Search.h"

#include <vector>
#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoSearchServiceModule : public Search::SdkModel::ISearchServiceModule, private Eegeo::NonCopyable
                {
                private:
                    IEegeoSearchQueryFactory* m_pEegeoSearchQueryFactory;
                    IEegeoParser* m_pEegeoParser;
                    Search::SdkModel::ISearchService* m_pSearchService;
                public:
                    EegeoSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                 Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                 Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                 const std::vector<std::string>& availableCategories,
                                                 const std::string& apiKey);
                    
                    ~EegeoSearchServiceModule();
                    
                    Search::SdkModel::ISearchService& GetSearchService() const;
                    
                    std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
                };
            }
        }
    }
}