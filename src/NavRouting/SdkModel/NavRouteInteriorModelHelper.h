// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "InteriorsModelRepository.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRouteInteriorModelHelper
            {
            public:
                NavRouteInteriorModelHelper() {};

                static bool TryGetIndoorMapFloorId(const Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                   const std::string& indoorMapId,
                                                   const int floorIndex,
                                                   int& out_floorId);
            };
        }
    }
}
