// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Compass
    {
        class CompassHeadingUpdateMessage
        {
        private:
            float m_headingRadians;

        public:
            CompassHeadingUpdateMessage(float headingRadians);

            float GetHeadingRadians() const;
        };
    }
}
