// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PlaceJumpsModel.h"

namespace ExampleApp
{
	namespace PlaceJumps
	{
		class PlaceJumpSelectedMessage
		{
			PlaceJumpModel m_placeJumpModel;

		public:
			PlaceJumpSelectedMessage(const PlaceJumpModel& placeJumpModel);

			const PlaceJumpModel& Model() const;
		};
	}
}
