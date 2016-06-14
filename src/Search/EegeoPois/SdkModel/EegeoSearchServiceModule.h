// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"

#include "Types.h"
#include "UrlHelpers.h"
#include "Web.h"
#include "EegeoPois.h"
#include "NetIncludes.h"
#include "Search.h"
#include "Interiors.h"
#include "ICategoryIconMapper.h"

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

                    SearchResultPoi::SdkModel::ICategoryIconMapper *m_pCategoryIconMapper;
                    EegeoReadableTagMapper *m_pReadableTagMapper;
                public:
                    EegeoSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                             Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                             Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                             const std::vector<std::string>& availableCategories,
                                             const std::string& serviceUrl,
                                             const std::string& apiKey,
                                             const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel);
                    
                    ~EegeoSearchServiceModule();
                    
                    Search::SdkModel::ISearchService& GetSearchService() const;
                    
                    std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
                };
            }
        }
    }
}