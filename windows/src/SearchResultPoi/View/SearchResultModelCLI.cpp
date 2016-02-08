// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultModelCLI.h"
#include "ReflectionHelpers.h"

namespace ExampleApp
{
	SearchResultModelCLI::SearchResultModelCLI(const Search::SdkModel::SearchResultModel& searchResultModel)
		: m_pSearchResultModel(NULL)
	{
		m_pSearchResultModel = Eegeo_NEW(Search::SdkModel::SearchResultModel)(searchResultModel);
	};

	SearchResultModelCLI::~SearchResultModelCLI()
	{
		Eegeo_DELETE m_pSearchResultModel;
		m_pSearchResultModel = NULL;
	}

	System::String^ SearchResultModelCLI::Title::get()
	{
		return Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_pSearchResultModel->GetTitle());
	}

	System::String^ SearchResultModelCLI::Subtitle::get()
	{
		return Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_pSearchResultModel->GetSubtitle());
	}

	System::String^ SearchResultModelCLI::JsonData::get()
	{
		return Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_pSearchResultModel->GetJsonData());
	}

	System::String^ SearchResultModelCLI::Category::get()
	{
		return Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_pSearchResultModel->GetCategory());
	}

	System::String^ SearchResultModelCLI::Vendor::get()
	{
		return Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_pSearchResultModel->GetVendor());
	}

	array<System::String^>^ SearchResultModelCLI::HumanReadableCategories::get()
	{
		const std::vector<std::string>& humanReadableCategories(m_pSearchResultModel->GetHumanReadableCategories());
		array<System::String^>^ humanCategoriesArray = gcnew array<System::String^>(static_cast<int>(humanReadableCategories.size()));

		for (size_t i = 0; i < humanReadableCategories.size(); ++i)
		{
			const std::string& categoryString(humanReadableCategories[i]);
			humanCategoriesArray[static_cast<int>(i)] = Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(categoryString);
		}

		return humanCategoriesArray;
	}
}
