// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldPinsInFocusModel.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        class WorldPinGainedFocusMessage
        {
            SdkModel::WorldPinsInFocusModel m_focussedModel;
            Eegeo::v2 m_screenLocation;

        public:
            WorldPinGainedFocusMessage(const SdkModel::WorldPinsInFocusModel& focussedModel, const Eegeo::v2& screenLocation);

            const SdkModel::WorldPinsInFocusModel& FocussedModel() const;
            const Eegeo::v2& ScreenLocation() const;
        };
    }
}
