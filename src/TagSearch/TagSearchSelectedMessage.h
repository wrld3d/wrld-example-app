// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace TagSearch
    {
        class TagSearchSelectedMessage
        {
            std::string m_tag;
            float m_radius;
            bool m_hasRadius;
            bool m_allowInteriorSearch;

        public:
            TagSearchSelectedMessage(
                const std::string& tag,
                bool allowInteriorSearch
            );
            
            TagSearchSelectedMessage(
                 const std::string& tag,
                 bool allowInteriorSearch,
                 float radius
              );

            const std::string& Tag() const;
            const bool HasRadius() const;
            const bool InteriorSearchAllowed() const;
            const float Radius() const;
        };
    }
}
