// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CategorySearchModel.h"
#include "writer.h"
#include "stringbuffer.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace View
        {
            CategorySearchModel::CategorySearchModel(const std::string& name,
                                                     const std::string& searchCategory,
                                                     bool interior,
                                                     const std::string& icon,
                                                     bool visibleInSearchMenu)
                : m_name(name)
                , m_searchCategory(searchCategory)
                , m_interior(interior)
                , m_icon(icon)
                , m_visibleInSearchMenu(visibleInSearchMenu)
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
            
            bool CategorySearchModel::Interior() const
            {
                return m_interior;
            }
            
            bool CategorySearchModel::IsVisibleInSearchMenu() const
            {
                return m_visibleInSearchMenu;
            }
        }
    }
}
