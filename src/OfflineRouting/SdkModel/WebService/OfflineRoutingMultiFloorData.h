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
                struct OfflineRoutingMultiFloorData
                {
                    int id;
                    std::string type;
                    std::string name;
                    std::vector<int> levels;
                    std::vector<Eegeo::Space::LatLong> coordinates;

                    OfflineRoutingMultiFloorData()
                    : id(0)
                    , type("")
                    , name("")
                    {
                    }
                };
            }
        }
    }
}
