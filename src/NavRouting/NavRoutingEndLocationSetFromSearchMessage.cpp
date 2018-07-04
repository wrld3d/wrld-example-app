// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingEndLocationSetFromSearchMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingEndLocationSetFromSearchMessage::NavRoutingEndLocationSetFromSearchMessage(SearchNavigationData data)
                : m_data(data)
        {

        }

        const SearchNavigationData& NavRoutingEndLocationSetFromSearchMessage::GetSearchData() const
        {
            return m_data;
        }
    }
}
