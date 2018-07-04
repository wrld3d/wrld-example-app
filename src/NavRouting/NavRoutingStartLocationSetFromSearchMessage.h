#pragma once

#include "SearchNavigationData.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingStartLocationSetFromSearchMessage
        {
        private:
            const SearchNavigationData m_data;

        public:
            NavRoutingStartLocationSetFromSearchMessage(SearchNavigationData data);

            const SearchNavigationData& GetSearchData() const;
        };
    }
}
