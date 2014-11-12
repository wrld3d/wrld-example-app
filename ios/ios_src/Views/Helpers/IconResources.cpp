// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "IconResources.h"

namespace
{
bool Contains(const std::string& string, const std::string& searchFor)
{
	return string.find(searchFor) != std::string::npos;
}
}

namespace ExampleApp
{
namespace Helpers
{
namespace IconResources
{
std::string GetCategoryMatch(std::string category)
{
	std::transform(category.begin(), category.end(), category.begin(), ::tolower);

	if(Contains(category, "caf\xc3\xa9") || Contains(category, "cafe") || Contains(category, "coffee"))
	{
		return "coffee";
	}
	if(Contains(category, "nightlife") || Contains(category, "night life"))
	{
		return "nightlife";
	}
	if(Contains(category, "museum") || category == "arts")
	{
		return "arts";
	}
	if(Contains(category, "park"))
	{
		return "park";
	}
	if(Contains(category, "bank"))
	{
		return "bank";
	}
	if(Contains(category, "hotel"))
	{
		return "hotel";
	}
	if(Contains(category, "restaurant") || Contains(category, "food"))
	{
		return "food";
	}

	return "misc";
}

std::string GetSmallIconForCategory(const std::string& category)
{
	std::string matchedCategory = GetCategoryMatch(category);
	return GetSmallIconPathForResourceName(matchedCategory);
}

std::string GetSmallIconPathForResourceName(const std::string& resource)
{
	return "icon1_" + resource;
}

std::string GetSearchResultIconPathForResourceName(const std::string& resource)
{
	std::string matchedCategory = GetCategoryMatch(resource);
	return "icon2_" + matchedCategory;
}
}
}
}
