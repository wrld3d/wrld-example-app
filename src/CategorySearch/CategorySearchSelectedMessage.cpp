// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CategorySearchSelectedMessage.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        CategorySearchSelectedMessage::CategorySearchSelectedMessage(
            const std::string& category,
            bool interior
        )
            : m_category(category)
            , m_interior(interior)
            , m_hasRadius(false)
            , m_radius(0.f)
        {
        }
        
        CategorySearchSelectedMessage::CategorySearchSelectedMessage(
                                                                     const std::string& category,
                                                                     bool interior,
                                                                     float radius
                                                                     )
        : m_category(category)
        , m_interior(interior)
        , m_hasRadius(true)
        , m_radius(radius)
        {
        }

        const std::string& CategorySearchSelectedMessage::Category() const
        {
            return m_category;
        }
        
        const bool CategorySearchSelectedMessage::Interior() const
        {
            return m_interior;
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
