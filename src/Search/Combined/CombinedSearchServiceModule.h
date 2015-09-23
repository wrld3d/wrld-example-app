// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"

#include <map>
#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace Combined
        {
            class CombinedSearchServiceModule : public SdkModel::ISearchServiceModule
            {
            private:
                SdkModel::ISearchService* m_pSearchService;
                
                std::vector<CategorySearch::View::CategorySearchModel> m_categorySearchModels;
                
            public:
                CombinedSearchServiceModule(std::map<std::string, SdkModel::ISearchServiceModule*> searchServiceModules);
                
                ~CombinedSearchServiceModule();
                
                SdkModel::ISearchService& GetSearchService() const;
                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
                
            };
        }
    }
}