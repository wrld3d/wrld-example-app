// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "ISearchProvider.h"

#import <WrldSearchWidget/WrldSearchWidget.h>

namespace ExampleApp
{
    namespace SearchProviders
    {
        class SearchProvider : public SearchMenu::View::ISearchProvider, private Eegeo::NonCopyable
        {
        private:
            typedef SearchMenu::View::ISearchProvider::TSearchResults TSearchResults;

            Eegeo::Helpers::CallbackCollection1<const std::string&> m_autocompleteSuggestionsCallbacks;
            Eegeo::Helpers::CallbackCollection1<const std::string&> m_searchPerformedCallbacks;
            Eegeo::Helpers::CallbackCollection2<const std::string&, const SearchMenu::View::QueryContext&> m_searchWithContextCallbacks;
            Eegeo::Helpers::CallbackCollection0 m_searchCancelledCallbacks;
            Eegeo::Helpers::CallbackCollection0 m_suggestionsCancelledCallbacks;
            WRLDSearchRequest* m_pCurrentRequest;
            WRLDSearchRequest* m_pCurrentSuggestion;

        public:
            SearchProvider();
            ~SearchProvider();

            void InsertAutocompleteSuggestionsCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);
            void RemoveAutocompleteSuggestionsCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);
            
            void InsertSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);
            void RemoveSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);

            void InsertSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&, const SearchMenu::View::QueryContext&>& callback);
            void RemoveSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&, const SearchMenu::View::QueryContext&>& callback);

            void InsertSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback);
            void RemoveSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback);
            
            void InsertSuggestionsCancelledCallback(Eegeo::Helpers::ICallback0& callback);
            void RemoveSuggestionsCancelledCallback(Eegeo::Helpers::ICallback0& callback);

            void OnSearchResponseReceived(const bool success, const TSearchResults& searchResults);
            void OnAutocompleteSuggestionsResponseReceived(const bool success, const TSearchResults& searchResults);

            void UpdateResults(const bool success, const TSearchResults& searchResults, WRLDSearchRequest* searchRequest);
            void CancelAutocompleteRequest();

            void PerformSearch(WRLDSearchRequest* searchRequest);
            void PerformAutocompleteSuggestions(WRLDSearchRequest* searchRequest);
        };
    }
}
