// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Compass
    {
        class CompassIsRotatingStateChangedMessage
        {
        public:
            CompassIsRotatingStateChangedMessage(bool isRotating)
                : m_isRotating(isRotating)
            {}

            bool IsRotating() const
            {
                return m_isRotating;
            }

        private:
            bool m_isRotating;
        };
    }
}
