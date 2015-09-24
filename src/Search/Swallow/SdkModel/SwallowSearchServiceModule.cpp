// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchServiceModule.h"

#include "SwallowSearchConstants.h"
#include "SwallowSearchService.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowSearchServiceModule::SwallowSearchServiceModule(PoiDb::IPoiDbModule& poiDbModule)
                : m_pSearchService(NULL)
                {
                    m_pSearchService = Eegeo_NEW(SwallowSearchService)(SearchConstants::GetCategories(),
                                                                       poiDbModule);
                }
                    
                SwallowSearchServiceModule::~SwallowSearchServiceModule()
                {
                    Eegeo_DELETE m_pSearchService;
                }
                    
                Search::SdkModel::ISearchService& SwallowSearchServiceModule::GetSearchService() const
                {
                    return *m_pSearchService;
                }
                    
                std::vector<CategorySearch::View::CategorySearchModel> SwallowSearchServiceModule::GetCategorySearchModels() const
                {
                    return SearchConstants::GetCategorySearchModels();
                }
            }
        }
    }
}