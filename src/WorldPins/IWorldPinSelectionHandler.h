// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
	namespace WorldPins
	{
		class IWorldPinSelectionHandler
		{
		public:
			virtual ~IWorldPinSelectionHandler() { }

			virtual void SelectPin() = 0;
		};
	}
}
