// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchServicesResult.h"
#include "SearchVendorNames.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			SearchServicesResult::SearchServicesResult(const std::string& name,
													   const std::string& description,
													   const std::string& iconName,
													   int originalIndex,
													   const TSdkSearchResult& sdkSearchResult)
			: m_name(name)
			, m_description(description)
			, m_iconName(iconName)
			, m_originalIndex(originalIndex)
			, m_sdkSearchResult(sdkSearchResult)
			, m_vendorOrder(m_sortOrder.translate[sdkSearchResult.GetVendor()])
			{
			}

			struct SearchServicesResult::SortOrder SearchServicesResult::m_sortOrder;

			SearchServicesResult::SortOrder::SortOrder()
			{
				translate[Search::EegeoVendorName   ] = 1;
				translate[Search::YelpVendorName    ] = 2;
				translate[Search::GeoNamesVendorName] = 3;
			}

			const std::string& SearchServicesResult::GetName() const
            {
				return m_name;
            }

			const std::string& SearchServicesResult::GetDescription() const
            {
				return m_description;
            }

			const std::string& SearchServicesResult::GetIconName() const
            {
				return m_iconName;
            }

			int SearchServicesResult::GetOriginalIndex() const
			{
				return m_originalIndex;
			}

			const SearchServicesResult::TSdkSearchResult& SearchServicesResult::GetSdkSearchResult() const
			{
				return m_sdkSearchResult;
			}

			bool SearchServicesResult::operator< (const SearchServicesResult& other) const
			{
				return m_vendorOrder < other.m_vendorOrder;
			}
		}
	}
}
