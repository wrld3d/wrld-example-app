// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        class InteriorsLocationAuthorizationChangedMessage
        {
        public:
            InteriorsLocationAuthorizationChangedMessage(const bool isAuthorized)
            : m_isAuthorized(isAuthorized)
            {}

            const bool IsAuthorized() const
            {
                return m_isAuthorized;
            }

        private:
            bool m_isAuthorized;
        };
    }
}
