// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavigateToMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavigateToMessage::NavigateToMessage(SearchNavigationData data)
        : m_data(data)
        {

        }

        const SearchNavigationData& NavigateToMessage::GetSearchData() const
        {
            return m_data;
        }
    }
}
