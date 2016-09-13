// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

//#include "ISearchServiceModule.h"
#include "Interiors.h"
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
/*                class CombinedSearchServiceModule : public Search::SdkModel::ISearchServiceModule
                {
                private:
                    std::shared_ptr<Search::SdkModel::ISearchService> m_searchService;
                    
                    std::vector<TagSearch::View::TagSearchModel> m_tagSearchModels;
                    
                public:
                    CombinedSearchServiceModule(std::map<std::string, std::shared_ptr<Search::SdkModel::ISearchServiceModule>>& searchServiceModules,
                                                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel);
                    
                    ~CombinedSearchServiceModule();

                    const std::shared_ptr<Search::SdkModel::ISearchService> GetSearchService() const;
                    
                    std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
                    
                }; */
            }
        }
    }
}