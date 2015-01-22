// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "PlaceJumps.h"
#include "PlaceJumpsModel.h"
#include <string>
#include <vector>

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace View
        {
            namespace PlaceJumpsDataParser
            {
                bool ParsePlaceJumps(const std::string& json, std::vector<PlaceJumpModel>&  out_placeJumpModel);
            }
        }
    }
}
