// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingSearchForLocationMessage
        {
        private:
            bool m_isSearching;
            bool m_isStartLocation;

        public:
            NavRoutingSearchForLocationMessage(bool isSearching, bool isStartLocation);

            bool IsSearching() const { return m_isSearching; }
            bool IsStartLocation() const { return m_isStartLocation; }
        };
    }
}