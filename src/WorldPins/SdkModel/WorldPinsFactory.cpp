// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsFactory.h"
#include "Pin.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            WorldPinsFactory::WorldPinsFactory()
                : m_lastId(0)
            {

            }

            WorldPinsFactory::~WorldPinsFactory()
            {

            }
            
            Eegeo::Pins::Pin* WorldPinsFactory::CreatePin(const Eegeo::Space::LatLong& location,
                                                          int iconIndex,
                                                          float heightAboveTerrainInMetres)
            {
                WorldPinItemModel::WorldPinItemModelId pinId = m_lastId ++;
                return Eegeo_NEW(Eegeo::Pins::Pin)(pinId, location, heightAboveTerrainInMetres, iconIndex, NULL);
            }
        }
    }
}
