// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CategorySearchSelectedMessage.h"

namespace ExampleApp
{
	namespace CategorySearch
	{
		CategorySearchSelectedMessage::CategorySearchSelectedMessage(
			const std::string& category
		)
			: m_category(category)
		{
		}

		const std::string& CategorySearchSelectedMessage::Category() const
		{
			return m_category;
		}
	}
}
