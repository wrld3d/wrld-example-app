// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingStartLocationSetFromSearchMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingStartLocationSetFromSearchMessage::NavRoutingStartLocationSetFromSearchMessage(SearchNavigationData data)
                : m_data(data)
        {

        }

        const SearchNavigationData& NavRoutingStartLocationSetFromSearchMessage::GetSearchData() const
        {
            return m_data;
        }
    }
}
