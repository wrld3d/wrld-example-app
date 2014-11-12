// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class ISearchResultOnMapScaleController
		{
		public:
			virtual ~ISearchResultOnMapScaleController() { }

			virtual void Update(float deltaSeconds) = 0;
		};
	}
}
