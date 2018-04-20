//
// Created by david.crooks on 13/03/2018.
//
#pragma once

#include <string>

namespace ExampleApp
{
    namespace SearchMenu
    {
        class AutocompleteSuggestionsMessage
        {
            std::string m_searchQuery;

        public:
            AutocompleteSuggestionsMessage(const std::string& searchQuery);

            const std::string& SearchQuery() const;

        };
    }
}
