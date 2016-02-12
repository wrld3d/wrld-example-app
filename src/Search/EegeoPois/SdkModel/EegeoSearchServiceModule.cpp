// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoSearchServiceModule.h"

#include "EegeoJsonParser.h"
#include "EegeoSearchQueryFactory.h"
#include "EegeoSearchService.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                EegeoSearchServiceModule::EegeoSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                           Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                                           Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                                           const std::vector<std::string>& availableCategories,
                                                                           const std::string& apiKey)
                : m_pEegeoSearchQueryFactory(NULL)
                , m_pEegeoParser(NULL)
                , m_pSearchService(NULL)
                {
                    m_pEegeoSearchQueryFactory = Eegeo_NEW(EegeoSearchQueryFactory)(webRequestFactory,
                                                                                            urlEncoder,
                                                                                            apiKey);
                    m_pEegeoParser = Eegeo_NEW(EegeoJsonParser)();
                    
                    m_pSearchService = Eegeo_NEW(EegeoSearchService)(*m_pEegeoSearchQueryFactory,
                                                                        *m_pEegeoParser,
                                                                        networkCapabilities,
                                                                         availableCategories);
                }
                
                EegeoSearchServiceModule::~EegeoSearchServiceModule()
                {
                    Eegeo_DELETE m_pSearchService;
                    Eegeo_DELETE m_pEegeoParser;
                    Eegeo_DELETE m_pEegeoSearchQueryFactory;
                }
                
                Search::SdkModel::ISearchService& EegeoSearchServiceModule::GetSearchService() const
                {
                    return *m_pSearchService;
                }
                
                std::vector<CategorySearch::View::CategorySearchModel> EegeoSearchServiceModule::GetCategorySearchModels() const
                {
                    return std::vector<CategorySearch::View::CategorySearchModel>();
                }
            }
        }
    }
}
