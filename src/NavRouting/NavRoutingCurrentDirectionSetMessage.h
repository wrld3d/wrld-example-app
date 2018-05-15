// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingCurrentDirectionSetMessage
        {
        private:
            int m_directionIndex;

        public:
            NavRoutingCurrentDirectionSetMessage(int directionIndex);

            int GetDirectionIndex() const;
        };
    }
}
