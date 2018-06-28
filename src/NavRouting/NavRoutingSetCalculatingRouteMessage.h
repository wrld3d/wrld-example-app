// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingSetCalculatingRouteMessage
        {
        private:
            bool m_calculatingRoute;

        public:
            NavRoutingSetCalculatingRouteMessage(bool calculatingRoute);

            bool GetShouldCalculatingRoute() const;
        };
    }
}
