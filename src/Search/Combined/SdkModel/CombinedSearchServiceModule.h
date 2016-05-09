// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"
#include "AppModes.h"

#include <map>
#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace Combined
        {
            namespace SdkModel
            {
                class CombinedSearchServiceModule : public Search::SdkModel::ISearchServiceModule
                {
                private:
                    Search::SdkModel::ISearchService* m_pSearchService;
                    
                    std::vector<CategorySearch::View::CategorySearchModel> m_categorySearchModels;
                    
                public:
                    CombinedSearchServiceModule(std::map<std::string, Search::SdkModel::ISearchServiceModule*> searchServiceModules,
                                                AppModes::SdkModel::IAppModeModel& appModeModel);
                    
                    ~CombinedSearchServiceModule();
                    
                    Search::SdkModel::ISearchService& GetSearchService() const;
                    
                    std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
                    
                };
            }
        }
    }
}