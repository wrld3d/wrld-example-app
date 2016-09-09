// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TagSearchSelectedMessage.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        TagSearchSelectedMessage::TagSearchSelectedMessage(
            const std::string& tag,
            bool allowInteriorSearch
        )
            : m_tag(tag)
            , m_allowInteriorSearch(allowInteriorSearch)
            , m_hasRadius(false)
            , m_radius(0.f)
        {
        }
        
        TagSearchSelectedMessage::TagSearchSelectedMessage(
                const std::string& tag,
                bool allowInteriorSearch,
                float radius)
        : m_tag(tag)
        , m_allowInteriorSearch(allowInteriorSearch)
        , m_hasRadius(true)
        , m_radius(radius)
        {
        }

        const std::string& TagSearchSelectedMessage::Tag() const
        {
            return m_tag;
        }
        
        const bool TagSearchSelectedMessage::InteriorSearchAllowed() const
        {
            return m_allowInteriorSearch;
        }
        
        const bool TagSearchSelectedMessage::HasRadius() const
        {
            return m_hasRadius;
        }
        
        const float TagSearchSelectedMessage::Radius() const
        {
            return m_radius;
        }
    }
}
