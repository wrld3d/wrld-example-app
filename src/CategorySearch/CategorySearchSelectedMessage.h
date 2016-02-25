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
            bool m_interior;

        public:
            CategorySearchSelectedMessage(
                const std::string& category,
                bool interior
            );
            
            CategorySearchSelectedMessage(
                 const std::string& category,
                 bool interior,
                 float radius
              );

            const std::string& Category() const;
            const bool HasRadius() const;
            const bool Interior() const;
            const float Radius() const;
        };
    }
}
