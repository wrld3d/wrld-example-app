// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        class InteriorsLocationAvailabilityChangedMessage
        {
        public:
            InteriorsLocationAvailabilityChangedMessage(const bool isLocationAvailable)
                : m_isLocationAvailable(isLocationAvailable)
            {}

            const bool IsLocationAvailable() const
            {
                return m_isLocationAvailable;
            }

        private:
            bool m_isLocationAvailable;
        };
    }
}
