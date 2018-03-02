// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "SearchResultModel.h"
#include "CallbackCollection.h"
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
				typedef std::vector<Search::SdkModel::SearchResultModel> TSearchResults;

				virtual void InsertSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;
				virtual void RemoveSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;

				virtual void InsertSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback) = 0;
				virtual void RemoveSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback) = 0;

				virtual void OnSearchResponseReceived(const TSearchResults& searchResults) = 0;
			};
		}
	}
}
