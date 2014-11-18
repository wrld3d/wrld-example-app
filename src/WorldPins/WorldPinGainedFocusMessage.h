// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "WorldPinsInFocusModel.h"
#include "VectorMath.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class WorldPinGainedFocusMessage
		{
            WorldPinsInFocusModel m_focussedModel;
			Eegeo::v2 m_screenLocation;

		public:
			WorldPinGainedFocusMessage(const WorldPinsInFocusModel& focussedModel, const Eegeo::v2& screenLocation)
				: m_focussedModel(focussedModel)
				, m_screenLocation(screenLocation)
			{

			}

			const WorldPinsInFocusModel& FocussedModel() const
			{
				return m_focussedModel;
			}

			const Eegeo::v2& ScreenLocation() const
			{
				return m_screenLocation;
			}
		};
	}
}
