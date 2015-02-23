// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinGainedFocusMessage.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        WorldPinGainedFocusMessage::WorldPinGainedFocusMessage(const SdkModel::WorldPinsInFocusModel& focussedModel, const Eegeo::v2& screenLocation)
            : m_focussedModel(focussedModel)
            , m_screenLocation(screenLocation)
        {

        }

        const SdkModel::WorldPinsInFocusModel& WorldPinGainedFocusMessage::FocussedModel() const
        {
            return m_focussedModel;
        }

        const Eegeo::v2& WorldPinGainedFocusMessage::ScreenLocation() const
        {
            return m_screenLocation;
        }
    }
}
