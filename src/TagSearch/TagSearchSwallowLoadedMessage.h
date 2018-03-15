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

        public:
            TagSearchSwallowLoadedMessage(const std::string key, const std::string tag)
            : m_key(key)
            , m_tag(tag)
            {
            }

            const std::string& Key() const { return m_key; }
            const std::string& Tag() const { return m_tag; }
        };
    }
}
