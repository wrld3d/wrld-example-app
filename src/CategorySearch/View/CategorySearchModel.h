// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace View
        {
            class CategorySearchModel
            {
                std::string m_name;
                std::string m_searchCategory;
                bool m_interior;
                std::string m_icon;
                bool m_visibleInSearchMenu;

            public:
                CategorySearchModel(const std::string& name, const std::string& searchCategory, bool interior, const std::string& icon, bool visibleInSearchMenu);

                const std::string& Name() const;

                const std::string& SearchCategory() const;

                const std::string& Icon() const;
                
                bool Interior() const;
                
                bool IsVisibleInSearchMenu() const;
            };
        }
    }
}
