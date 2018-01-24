// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingRerouteDialogClosedMessage
        {
        private:
            bool m_shouldReroute;

        public:
            NavRoutingRerouteDialogClosedMessage(bool shouldReroute);

            bool GetShouldReroute() const;
        };
    }
}
