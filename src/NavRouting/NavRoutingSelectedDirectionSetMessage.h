// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingSelectedDirectionSetMessage
        {
        private:
            int m_directionIndex;

        public:
            NavRoutingSelectedDirectionSetMessage(int directionIndex);

            int GetDirectionIndex() const;
        };
    }
}
