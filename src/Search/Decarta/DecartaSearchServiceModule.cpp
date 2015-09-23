// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DecartaSearchServiceModule.h"

#include "DecartaSearchConstants.h"
#include "DecartaSearchJsonParser.h"
#include "DecartaSearchService.h"
#include "ApiKey.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Decarta
        {
            DecartaSearchServiceModule::DecartaSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory,
                                                                   Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder)
            {
                m_pSearchResultParser = Eegeo_NEW(Decarta::DecartaSearchJsonParser);
                
                m_pSearchService = Eegeo_NEW(Decarta::DecartaSearchService)(ExampleApp::DecartaApiKey,
                                                                            *m_pSearchResultParser,
                                                                            urlEncoder,
                                                                            webLoadRequestFactory,
                                                                            Decarta::SearchConstants::GetCategories());
            }
            
            DecartaSearchServiceModule::~DecartaSearchServiceModule()
            {
                Eegeo_DELETE m_pSearchService;
                Eegeo_DELETE m_pSearchResultParser;
            }
            
            SdkModel::ISearchService& DecartaSearchServiceModule::GetSearchService() const
            {
                return *m_pSearchService;
            }
            
            std::vector<CategorySearch::View::CategorySearchModel> DecartaSearchServiceModule::GetCategorySearchModels() const
            {
                return Decarta::SearchConstants::GetCategorySearchModels();
            }
        }
    }
}