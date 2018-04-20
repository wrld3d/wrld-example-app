// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace TagSearch
    {
        class TagSearchSwallowLoadedMessage
        {
        private:
            std::string m_key;
            std::string m_tag;
            bool m_shouldTryInterior;
            bool m_hasRadiusOverride;
            float m_radiusOverride;

        public:
            TagSearchSwallowLoadedMessage(const std::string key, const std::string tag,
                                          bool shouldTryInterior,
                                          bool hasRadiusOverride, float radiusOverride)
            : m_key(key)
            , m_tag(tag)
            , m_shouldTryInterior(shouldTryInterior)
            , m_hasRadiusOverride(hasRadiusOverride)
            , m_radiusOverride(radiusOverride)
            {
            }

            const std::string& Key() const { return m_key; }
            const std::string& Tag() const { return m_tag; }
            bool ShouldTryInterior() const { return m_shouldTryInterior; }
            bool HasRadiusOverride() const { return m_hasRadiusOverride; }
            float RadiusOverride()   const { return m_radiusOverride; }
        };
    }
}
