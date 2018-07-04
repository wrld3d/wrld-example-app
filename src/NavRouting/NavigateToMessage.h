// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchNavigationData.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavigateToMessage
        {
        private:
            const SearchNavigationData m_data;

        public:
            NavigateToMessage(SearchNavigationData data);

            const SearchNavigationData& GetSearchData() const;
        };
    }
}
