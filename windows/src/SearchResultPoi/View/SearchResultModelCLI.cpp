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

	System::String^ SearchResultModelCLI::IconKey::get()
	{
		return Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_pSearchResultModel->GetIconKey());
	}

	System::String^ SearchResultModelCLI::Vendor::get()
	{
		return Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_pSearchResultModel->GetVendor());
	}

	array<System::String^>^ SearchResultModelCLI::HumanReadableTags::get()
	{
		const std::vector<std::string>& humanReadableTags(m_pSearchResultModel->GetHumanReadableTags());
		array<System::String^>^ humanReadableTagsArray = gcnew array<System::String^>(static_cast<int>(humanReadableTags.size()));

		for (size_t i = 0; i < humanReadableTags.size(); ++i)
		{
			const std::string& tagString(humanReadableTags[i]);
			humanReadableTagsArray[static_cast<int>(i)] = Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(tagString);
		}

		return humanReadableTagsArray;
	}
}
