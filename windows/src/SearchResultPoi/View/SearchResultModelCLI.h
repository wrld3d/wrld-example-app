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

		property System::String^ Title { System::String^ get(); }

		property System::String^ Subtitle { System::String^ get(); }

		property System::String^ JsonData { System::String^ get(); }

		property System::String^ IconKey { System::String^ get(); }

		property System::String^ Vendor { System::String^ get(); }

		property array<System::String^>^ HumanReadableTags { array<System::String^>^ get(); }
	};
}

