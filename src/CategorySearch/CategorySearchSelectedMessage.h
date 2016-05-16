// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace CategorySearch
    {
        class CategorySearchSelectedMessage
        {
            std::string m_category;
            float m_radius;
            bool m_hasRadius;
            bool m_allowInteriorSearch;

        public:
            CategorySearchSelectedMessage(
                const std::string& category,
                bool allowInteriorSearch
            );
            
            CategorySearchSelectedMessage(
                 const std::string& category,
                 bool allowInteriorSearch,
                 float radius
              );

            const std::string& Category() const;
            const bool HasRadius() const;
            const bool InteriorSearchAllowed() const;
            const float Radius() const;
        };
    }
}
