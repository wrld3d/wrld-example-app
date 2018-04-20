//
// Created by david.crooks on 13/03/2018.
//

#include "AutocompleteSuggestionsMessage.h"


namespace ExampleApp {
    namespace SearchMenu {
        AutocompleteSuggestionsMessage::AutocompleteSuggestionsMessage(const std::string &searchQuery)
                : m_searchQuery(searchQuery)
        {

        }

        const std::string&AutocompleteSuggestionsMessage::SearchQuery() const
        {
            return m_searchQuery;
        }
    }
}