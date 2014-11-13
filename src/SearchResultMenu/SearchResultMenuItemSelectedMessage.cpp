// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultMenuItemSelectedMessage.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		SearchResultMenuItemSelectedMessage::SearchResultMenuItemSelectedMessage(
			const Eegeo::dv3& searchResultModelLocationEcef
		)
			: m_searchResultModelLocationEcef(searchResultModelLocationEcef)
		{
		}

		const Eegeo::dv3& SearchResultMenuItemSelectedMessage::SearchResultLocationEcef() const
		{
			return m_searchResultModelLocationEcef;
		}
	}
}
