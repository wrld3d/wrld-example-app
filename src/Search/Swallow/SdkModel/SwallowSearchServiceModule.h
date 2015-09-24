// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"

#include "Types.h"

#include "PoiDb.h"
#include "SwallowSearch.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class SwallowSearchServiceModule : public Search::SdkModel::ISearchServiceModule, private Eegeo::NonCopyable
                {
                private:
                    Search::SdkModel::ISearchService* m_pSearchService;
                    
                public:
                    SwallowSearchServiceModule(PoiDb::IPoiDbModule& poiDbModule);
                    
                    ~SwallowSearchServiceModule();
                    
                    Search::SdkModel::ISearchService& GetSearchService() const;
                    
                    std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
                };
            }
        }
    }
}