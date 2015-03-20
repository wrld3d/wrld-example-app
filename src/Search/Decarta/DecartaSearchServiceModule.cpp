// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DecartaSearchServiceModule.h"
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
                                                                            webLoadRequestFactory);
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
                // Some DeCarta categories from http://developer.decarta.com/Docs/REST/Search#category
                std::vector<ExampleApp::CategorySearch::View::CategorySearchModel> categories;
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Coffee", "coffee shop", "coffee"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Food", "restaurant", "food"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Nightlife", "night life", "nightlife"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Arts", "museum", "arts"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Hotels", "hotel", "hotel"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Parks", "park", "park"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Banks", "bank", "bank"));
                return categories;
            }
        }
    }
}