// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace CategorySearch
    {
        class CategorySearchSelectedMessage
        {
            std::string m_category;

        public:
            CategorySearchSelectedMessage(
                const std::string& category
            );

            const std::string& Category() const;
        };
    }
}
