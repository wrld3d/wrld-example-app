// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinsFactory.h"
#include "Pins.h"
#include "Space.h"
#include "WorldPinItemModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsFactory : public IWorldPinsFactory, private Eegeo::NonCopyable
            {
                WorldPinItemModel::WorldPinItemModelId m_lastId;
                
            public:
                WorldPinsFactory();
                
                ~WorldPinsFactory();
                
                Eegeo::Pins::Pin* CreatePin(const Eegeo::Space::LatLong& location,
                                            int iconIndex,
                                            float heightAboveTerrainInMetres);
            };
        }
    }
}
