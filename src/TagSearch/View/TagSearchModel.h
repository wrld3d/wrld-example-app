// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            class TagSearchModel
            {
                std::string m_name;
                std::string m_searchTag;
                std::string m_icon;
                bool m_visibleInSearchMenu;
                bool m_interior;

            public:
                TagSearchModel(const std::string& name, const std::string& searchTag, bool interior, const std::string& icon, bool visibleInSearchMenu);

                const std::string& Name() const;

                const std::string& SearchTag() const;

                const std::string& Icon() const;
                
                bool Interior() const;
                
                bool IsVisibleInSearchMenu() const;

                bool operator==(const TagSearchModel& rhs) const;

                bool operator!=(const TagSearchModel& rhs) const;
            };
        }
    }
}
