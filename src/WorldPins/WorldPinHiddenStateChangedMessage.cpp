// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinHiddenStateChangedMessage.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        WorldPinHiddenStateChangedMessage::WorldPinHiddenStateChangedMessage(const SdkModel::WorldPinItemModel& worldPinItemModel)
        : m_worldPinItemModel(worldPinItemModel)
        {
        }
    }
}