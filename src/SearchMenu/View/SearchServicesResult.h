// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "SearchResultModel.h"

#include <string>
#include <map>

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			class SearchServicesResult
			{
			public:
				typedef Search::SdkModel::SearchResultModel TSdkSearchResult;

			private:
				struct SortOrder
				{
					std::map<std::string, int> translate;

					SortOrder();
				};
				static SortOrder m_sortOrder;

				std::string m_name;
				std::string m_description;
				std::string m_iconName;

				int m_originalIndex;
				TSdkSearchResult m_sdkSearchResult;
				int m_vendorOrder;

			public:
				SearchServicesResult(const std::string& name,
									 const std::string& description,
									 const std::string& iconName,
									 int originalIndex,
									 const TSdkSearchResult& sdkSearchResult);

				const std::string& GetName() const;
				const std::string& GetDescription() const;
				const std::string& GetIconName() const;

				int GetOriginalIndex() const;
				const TSdkSearchResult& GetSdkSearchResult() const;

				bool operator< (const SearchServicesResult& other) const;
			};
		}
	}
}
