// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultModel.h"

namespace ExampleApp
{
	public ref class SearchResultModelCLI
	{
	private:
		Search::SdkModel::SearchResultModel* m_pSearchResultModel;
	public:
		SearchResultModelCLI(const Search::SdkModel::SearchResultModel& searchResultModel);

		~SearchResultModelCLI();

		System::String^ GetTitle();

		System::String^ GetSubtitle();

		System::String^ GetJsonData();

		System::String^ GetCategory();

		System::String^ GetVendor();

		array<System::String^>^ GetHumanReadableCategories();
	};
}

