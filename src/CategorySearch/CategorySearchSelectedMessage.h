// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
namespace CategorySearch
{
class CategorySearchSelectedMessage
{
	std::string m_category;

public:
	CategorySearchSelectedMessage(
	    const std::string& category
	)
		: m_category(category)
	{
	}

	const std::string& Category() const
	{
		return m_category;
	}
};
}
}
