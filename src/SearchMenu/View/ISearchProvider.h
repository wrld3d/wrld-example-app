// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "SearchServicesResult.h"
#include "CallbackCollection.h"
#include "QueryContext.h"
#include <vector>
#include <string>

namespace ExampleApp
{
	namespace SearchMenu
	{
		namespace View
		{
			class ISearchProvider
			{
			public:
				virtual ~ISearchProvider() { }
				typedef std::vector<SearchServicesResult> TSearchResults;

				virtual void InsertAutocompleteSuggestionsCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;
				virtual void RemoveAutocompleteSuggestionsCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;

				virtual void InsertSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;
				virtual void RemoveSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;

				virtual void InsertSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&, const QueryContext&>& callback) = 0;
				virtual void RemoveSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&, const QueryContext&>& callback) = 0;

				virtual void InsertSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback) = 0;
				virtual void RemoveSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback) = 0;

				virtual void InsertSuggestionsCancelledCallback(Eegeo::Helpers::ICallback0& callback) = 0;
				virtual void RemoveSuggestionsCancelledCallback(Eegeo::Helpers::ICallback0& callback) = 0;

				virtual void OnSearchResponseReceived(bool success, const TSearchResults& searchResults) = 0;
				virtual void OnAutocompleteSuggestionsResponseReceived(bool success, const TSearchResults& searchResults) = 0;
			};
		}
	}
}
