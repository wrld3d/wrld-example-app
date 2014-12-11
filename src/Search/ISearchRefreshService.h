// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "VectorMath.h"

namespace ExampleApp
{
	namespace Search
	{
		class ISearchRefreshService
		{
		public:
			virtual ~ISearchRefreshService() { }

			virtual void TryRefreshSearch(float deltaSeconds, const Eegeo::dv3& ecefLocation) = 0;
            virtual void SetEnabled(bool enabled) = 0;
            virtual const bool IsEnabled() const = 0;
		};
	}
}
