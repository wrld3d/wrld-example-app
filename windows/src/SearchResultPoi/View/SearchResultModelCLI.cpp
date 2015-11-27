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

	System::String^ SearchResultModelCLI::GetTitle()
	{
		return Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_pSearchResultModel->GetTitle());
	}

	System::String^ SearchResultModelCLI::GetSubtitle()
	{
		return Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_pSearchResultModel->GetSubtitle());
	}

	System::String^ SearchResultModelCLI::GetJsonData()
	{
		return Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_pSearchResultModel->GetJsonData());
	}

	System::String^ SearchResultModelCLI::GetCategory()
	{
		return Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_pSearchResultModel->GetCategory());
	}

	System::String^ SearchResultModelCLI::GetVendor()
	{
		return Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_pSearchResultModel->GetVendor());
	}

	array<System::String^>^ SearchResultModelCLI::GetHumanReadableCategories()
	{
		const std::vector<std::string>& humanReadableCategories(m_pSearchResultModel->GetHumanReadableCategories());
		array<System::String^>^ humanCategoriesArray = gcnew array<System::String^>(humanReadableCategories.size());

		for (size_t i = 0; i < humanReadableCategories.size(); ++i)
		{
			const std::string& categoryString(humanReadableCategories[i]);
			humanCategoriesArray[i] = Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(categoryString);
		}

		return humanCategoriesArray;
	}
}
