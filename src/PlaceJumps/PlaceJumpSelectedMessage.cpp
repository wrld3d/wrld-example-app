// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PlaceJumpSelectedMessage.h"

namespace ExampleApp
{
	namespace PlaceJumps
	{
		PlaceJumpSelectedMessage::PlaceJumpSelectedMessage(const PlaceJumpModel& placeJumpModel)
			: m_placeJumpModel(placeJumpModel)
		{
		}

		const PlaceJumpModel& PlaceJumpSelectedMessage::Model() const
		{
			return m_placeJumpModel;
		}
	}
}
