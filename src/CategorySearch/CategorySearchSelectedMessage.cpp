// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CategorySearchSelectedMessage.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        CategorySearchSelectedMessage::CategorySearchSelectedMessage(
            const std::string& category,
            bool allowInteriorSearch
        )
            : m_category(category)
            , m_allowInteriorSearch(allowInteriorSearch)
            , m_hasRadius(false)
            , m_radius(0.f)
        {
        }
        
        CategorySearchSelectedMessage::CategorySearchSelectedMessage(
                                                                     const std::string& category,
                                                                     bool allowInteriorSearch,
                                                                     float radius
                                                                     )
        : m_category(category)
        , m_allowInteriorSearch(allowInteriorSearch)
        , m_hasRadius(true)
        , m_radius(radius)
        {
        }

        const std::string& CategorySearchSelectedMessage::Category() const
        {
            return m_category;
        }
        
        const bool CategorySearchSelectedMessage::InteriorSearchAllowed() const
        {
            return m_allowInteriorSearch;
        }
        
        const bool CategorySearchSelectedMessage::HasRadius() const
        {
            return m_hasRadius;
        }
        
        const float CategorySearchSelectedMessage::Radius() const
        {
            return m_radius;
        }
    }
}
