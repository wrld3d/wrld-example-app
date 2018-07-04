#pragma once

#include "SearchNavigationData.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingEndLocationSetFromSearchMessage
        {
        private:
            const SearchNavigationData m_data;

        public:
            NavRoutingEndLocationSetFromSearchMessage(SearchNavigationData data);

            const SearchNavigationData& GetSearchData() const;
        };
    }
}
