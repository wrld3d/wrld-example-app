// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "ISearchServiceModule.h"
#include "Web.h"
#include "UrlHelpers.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Decarta
        {
            namespace SdkModel
            {
                class DecartaSearchServiceModule : public Search::SdkModel::ISearchServiceModule, private Eegeo::NonCopyable
                {
                    Search::SdkModel::ISearchService* m_pSearchService;
                    Search::SdkModel::ISearchResultParser* m_pSearchResultParser;
                    
                public:
                    DecartaSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory,
                                               Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder);
                    
                    ~DecartaSearchServiceModule();
                    
                    Search::SdkModel::ISearchService& GetSearchService() const;
                    
                    std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
                };
            }
        }
    }
}

