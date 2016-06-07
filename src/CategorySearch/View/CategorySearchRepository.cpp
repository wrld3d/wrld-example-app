// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CategorySearchRepository.h"
#include "SearchQuery.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace View
        {
            CategorySearchRepository::CategorySearchRepository(const std::vector<CategorySearchModel>& models)
                : m_models(models)
            {

            }

            bool CategorySearchRepository::TryGetCategorySearchNameByQuery(const std::string& query, std::string& out_name) const
            {
                for(std::vector<CategorySearchModel>::const_iterator it = m_models.begin(); it != m_models.end(); ++ it)
                {
                    const CategorySearchModel& categorySearchModel = *it;
                    if(categorySearchModel.SearchCategory() == query)
                    {
                        out_name = categorySearchModel.Name();
                        return true;
                    }
                }

                return false;
            }
            
            std::string GetPresentationStringForQuery(const ICategorySearchRepository& categorySearchRepository, const Search::SdkModel::SearchQuery& query)
            {
                if(query.IsCategory())
                {
                    std::string categoryName;
                    const bool foundName = categorySearchRepository.TryGetCategorySearchNameByQuery(query.Query(), categoryName);
                    Eegeo_ASSERT(foundName, "Unable to find name for category query %s.\n", query.Query().c_str());
                    return categoryName;
                }
                else
                {
                    return query.Query();
                }
            }
        }
    }
}
