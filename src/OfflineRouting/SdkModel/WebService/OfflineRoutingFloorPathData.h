// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "LatLongAltitude.h"

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace Webservice
            {
                struct OfflineRoutingFloorPathData
                {
                    int id;
                    std::string type;
                    std::string name;
                    bool isMultiFloor;
                    std::vector<int> levels;
                    std::vector<Eegeo::Space::LatLong> coordinates;
                    bool isOneWay;
                    int durationMultiplier;

                    OfflineRoutingFloorPathData()
                    : id(0)
                    , isMultiFloor(false)
                    , isOneWay(false)
                    , durationMultiplier(1)
                    {
                    }
                };
            }
        }
    }
}
