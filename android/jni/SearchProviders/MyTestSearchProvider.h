// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "ISearchProvider.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace SearchProviders
    {
		class MyTestSearchProvider : public SearchMenu::View::ISearchProvider, private Eegeo::NonCopyable
		{
		private:
			typedef SearchMenu::View::ISearchProvider::TSearchResults TSearchResults;
			Eegeo::Helpers::CallbackCollection1<const std::string&> m_autocompleteSuggestionsCallbacks;
			Eegeo::Helpers::CallbackCollection1<const std::string&> m_searchPerformedCallbacks;
			Eegeo::Helpers::CallbackCollection2<const std::string&, const SearchMenu::View::QueryContext&> m_searchWithContextCallbacks;
			Eegeo::Helpers::CallbackCollection0 m_searchCancelledCallbacks;
			Eegeo::Helpers::CallbackCollection0 m_suggestionsCancelledCallbacks;

			AndroidNativeState& m_nativeState;
			jclass m_javaClass;
			jobject m_javaInstance;
			jmethodID m_onSearchCompleted;
			jmethodID m_onAutocompleteSuggestionsCompleted;
		public:
			MyTestSearchProvider(AndroidNativeState& nativeState, bool showNavigationButtons);
			~MyTestSearchProvider();

			jobject GetJavaInstance();

			void InsertAutocompleteSuggestionsCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);
			void RemoveAutocompleteSuggestionsCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);

			void InsertSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);
			void RemoveSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);

			void InsertSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&,
																			const SearchMenu::View::QueryContext&>& callback);
			void RemoveSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&,
																			const SearchMenu::View::QueryContext&>& callback);

			void InsertSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback);
			void RemoveSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback);

			void InsertSuggestionsCancelledCallback(Eegeo::Helpers::ICallback0& callback);
			void RemoveSuggestionsCancelledCallback(Eegeo::Helpers::ICallback0& callback);

			void PerformAutocompleteSuggestions(const std::string& searchQuery);
			void PerformSearch(const std::string& searchQuery);
			void PerformSearchWithContext(const std::string& searchQuery,
										  const SearchMenu::View::QueryContext& queryContext);
			void CancelSearch();
			void CancelSuggestions();

			void OnSearchResponseReceived(const bool success, const TSearchResults& searchResults);
			void OnAutocompleteSuggestionsResponseReceived(const bool success, const TSearchResults& searchResults);
			void ResponseReceived(const bool success, const TSearchResults& searchResults,jmethodID methodId);
		};
    }
}
