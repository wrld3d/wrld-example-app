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

			Eegeo::Helpers::CallbackCollection1<const std::string&> m_searchPerformedCallbacks;
			Eegeo::Helpers::CallbackCollection2<const std::string&, const SearchMenu::View::QueryContext&> m_searchRefreshedCallbacks;
			Eegeo::Helpers::CallbackCollection0 m_searchCancelledCallbacks;

			AndroidNativeState& m_nativeState;
			jclass m_javaClass;
			jobject m_javaInstance;
			jmethodID m_onSearchCompleted;

		public:
			MyTestSearchProvider(AndroidNativeState& nativeState);
			~MyTestSearchProvider();

			jobject GetJavaInstance();

			void InsertSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);
			void RemoveSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);

			void InsertSearchRefreshedCallback(Eegeo::Helpers::ICallback2<const std::string&,
																		  const SearchMenu::View::QueryContext&>& callback);
			void RemoveSearchRefreshedCallback(Eegeo::Helpers::ICallback2<const std::string&,
																		  const SearchMenu::View::QueryContext&>& callback);

			void InsertSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback);
			void RemoveSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback);

			void PerformSearch(const std::string& searchQuery);
			void PerformSearchRefresh(const std::string& searchQuery,
									  const SearchMenu::View::QueryContext& queryContext);
			void CancelSearch();

			void OnSearchResponseReceived(const TSearchResults& searchResults);
		};
    }
}
