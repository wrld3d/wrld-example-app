// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingSearchForLocationMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingSearchForLocationMessage::NavRoutingSearchForLocationMessage(bool isSearching, bool isStartLocation)
        : m_isSearching(isSearching)
        , m_isStartLocation(isStartLocation)
        {

        }
    }
}