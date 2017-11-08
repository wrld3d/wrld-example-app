// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        class InteriorsHeadingChangedMessage
        {
        public:
            InteriorsHeadingChangedMessage(const double headingDegrees)
                    : m_headingDegrees(headingDegrees)
            {}

            const double HeadingDegrees() const
            {
                return m_headingDegrees;
            }

        private:
            double m_headingDegrees;
        };
    }
}
