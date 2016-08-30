// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <vector>
#include <string>
#include "CategorySearch.h"
#include "ICategorySearchRepository.h"
#include "CategorySearchModel.h"
#include "Types.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace View
        {
            class CategorySearchRepository : public ICategorySearchRepository, private Eegeo::NonCopyable
            {
                const std::shared_ptr<TCategories> m_models;

            public:
                CategorySearchRepository(const std::shared_ptr<TCategories>& models);

                bool TryGetCategorySearchNameByQuery(const std::string& query, std::string& out_name) const;
            };
        }
    }
}
