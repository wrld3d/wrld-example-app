// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingSelectedDirectionChangedMessage
        {
        private:
            int m_directionIndex;

        public:
            NavRoutingSelectedDirectionChangedMessage(int directionIndex);

            int GetDirectionIndex() const;
        };
    }
}
