// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "VectorMath.h"

namespace ExampleApp
{
namespace SearchResultMenu
{
class SearchResultMenuItemSelectedMessage
{
	Eegeo::dv3 m_searchResultModelLocationEcef;

public:
	SearchResultMenuItemSelectedMessage(
	    const Eegeo::dv3& searchResultModelLocationEcef
	)
		: m_searchResultModelLocationEcef(searchResultModelLocationEcef)
	{
	}

	const Eegeo::dv3& SearchResultLocationEcef() const
	{
		return m_searchResultModelLocationEcef;
	}
};
}
}
