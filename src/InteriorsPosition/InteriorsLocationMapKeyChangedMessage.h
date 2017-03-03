// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        class InteriorsLocationMapKeyChangedMessage
        {
        public:
            InteriorsLocationMapKeyChangedMessage(const std::string mapKey)
                : m_mapKey(mapKey)
            {
            }

            const std::string MapKey() const
            {
                return m_mapKey;
            }

        private:
            std::string m_mapKey;
        };
    }
}
