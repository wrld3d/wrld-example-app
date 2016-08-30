// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CombinedSearchServiceModule.h"
#include "CombinedSearchService.h"


namespace ExampleApp
{
    namespace Search
    {
        namespace Combined
        {
            namespace SdkModel
            {
/*                CombinedSearchServiceModule::CombinedSearchServiceModule(std::map<std::string, std::shared_ptr<Search::SdkModel::ISearchServiceModule>>& searchServiceModules,
                                                                         const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel)
                {
                    std::map<std::string, std::shared_ptr<Search::SdkModel::ISearchService>> searchServices;
                    
                    for(std::map<std::string, std::shared_ptr<Search::SdkModel::ISearchServiceModule>>::const_iterator it = searchServiceModules.begin(); it != searchServiceModules.end(); ++it)
                    {
                        searchServices[(*it).first] = (*it).second->GetSearchService();
                        std::vector<CategorySearch::View::CategorySearchModel> categorySearchModels = (*it).second->GetCategorySearchModels();
                        m_categorySearchModels.insert(m_categorySearchModels.end(), categorySearchModels.begin(), categorySearchModels.end());
                    }
                    
                    m_searchService = std::make_shared<CombinedSearchService>(searchServices, interiorInteractionModel);
                }
                
                CombinedSearchServiceModule::~CombinedSearchServiceModule()
                {
                }
                
                const std::shared_ptr<Search::SdkModel::ISearchService> CombinedSearchServiceModule::GetSearchService() const
                {
                    return m_searchService;
                }
                
                std::vector<CategorySearch::View::CategorySearchModel> CombinedSearchServiceModule::GetCategorySearchModels() const
                {
                    return m_categorySearchModels;
                } */
            }
        }
    }
}