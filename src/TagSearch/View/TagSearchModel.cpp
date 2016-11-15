// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TagSearchModel.h"
#include "writer.h"
#include "stringbuffer.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            TagSearchModel::TagSearchModel(const std::string& name,
                                                     const std::string& searchTag,
                                                     bool interior,
                                                     const std::string& icon,
                                                     bool visibleInSearchMenu)
                : m_name(name)
                , m_searchTag(searchTag)
                , m_interior(interior)
                , m_icon(icon)
                , m_visibleInSearchMenu(visibleInSearchMenu)
            {

            }

            const std::string& TagSearchModel::Name() const
            {
                return m_name;
            }

            const std::string& TagSearchModel::Icon() const
            {
                return m_icon;
            }

            const std::string& TagSearchModel::SearchTag() const
            {
                return m_searchTag;
            }
            
            bool TagSearchModel::Interior() const
            {
                return m_interior;
            }
            
            bool TagSearchModel::IsVisibleInSearchMenu() const
            {
                return m_visibleInSearchMenu;
            }

            bool TagSearchModel::operator == (const TagSearch::View::TagSearchModel& rhs) const
            {
                return m_name == rhs.m_name &&
                        m_searchTag == rhs.m_searchTag &&
                        m_interior == rhs.m_interior &&
                        m_icon == rhs.m_icon &&
                        m_visibleInSearchMenu == rhs.m_visibleInSearchMenu;
            }

            bool TagSearchModel::operator != (const TagSearch::View::TagSearchModel& rhs) const
            {
                return !(rhs == *this);
            }
        }
    }
}
