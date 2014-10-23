// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CategorySearchModel.h"
#include "writer.h"
#include "stringbuffer.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        CategorySearchModel::CategorySearchModel(const std::string& name,
                                                 const std::string& searchCategory,
                                                 const std::string& icon)
        : m_name(name)
        , m_searchCategory(searchCategory)
        , m_icon(icon)
        {
            
        }
        
        const std::string& CategorySearchModel::Name() const
        {
            return m_name;
        }
        
        const std::string& CategorySearchModel::Icon() const
        {
        	return m_icon;
        }

        const std::string& CategorySearchModel::SearchCategory() const
        {
            return m_searchCategory;
        }
    }
}
