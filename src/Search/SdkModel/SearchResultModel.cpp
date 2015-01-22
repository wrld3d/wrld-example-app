// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultModel.h"

namespace ExampleApp
{
	namespace Search
	{
		SearchResultModel::SearchResultModel(const std::string& identifier,
		                                     const std::string& title,
		                                     const Eegeo::Space::LatLong& location,
		                                     const std::string& phone,
		                                     const std::string& address,
		                                     const std::string& webUrl,
		                                     const std::string& category,
		                                     const std::string& vicinity)
			: m_identifier(identifier)
			, m_title(title)
			, m_location(location)
			, m_phone(phone)
			, m_address(address)
			, m_webUrl(webUrl)
			, m_category(category)
			, m_vicinity(vicinity)
		{

		}

		SearchResultModel::~SearchResultModel()
		{

		}

		const std::string& SearchResultModel::GetTitle() const
		{
			return m_title;
		}

		const std::string& SearchResultModel::GetIdentifier() const
		{
			return m_identifier;
		}

		const Eegeo::Space::LatLong& SearchResultModel::GetLocation() const
		{
			return m_location;
		}

		const std::string& SearchResultModel::GetPhone() const
		{
			return m_phone;
		}

		const std::string& SearchResultModel::GetAddress() const
		{
			return m_address;
		}

		const std::string& SearchResultModel::GetWebUrl() const
		{
			return m_webUrl;
		}

		const std::string& SearchResultModel::GetCategory() const
		{
			return m_category;
		}

		const std::string& SearchResultModel::GetVicinity() const
		{
			return m_vicinity;
		}
	}
}
