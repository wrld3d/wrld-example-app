// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "OfflineRoutingFloorPathData.h"

#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace Webservice
            {
                struct OfflineRoutingFloorData
                {
                    int floorId;
                    std::vector<OfflineRoutingFloorPathData> floorPaths;

                    OfflineRoutingFloorData()
                    : floorId(0)
                    {
                    }
                };
            }
        }
    }
}
