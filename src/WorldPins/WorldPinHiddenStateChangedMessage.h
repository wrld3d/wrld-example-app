// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "WorldPins.h"

namespace ExampleApp
{
    namespace WorldPins
    {
    
        class WorldPinHiddenStateChangedMessage
        {
        public:
            WorldPinHiddenStateChangedMessage(const SdkModel::WorldPinItemModel& worldPinItemModel);
            
            const SdkModel::WorldPinItemModel& GetWorldPin() const { return m_worldPinItemModel; }
            
        private:
            const SdkModel::WorldPinItemModel& m_worldPinItemModel;
        };
    }
}