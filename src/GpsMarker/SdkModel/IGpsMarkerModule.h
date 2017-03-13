// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "GpsMarker.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class IGpsMarkerModule
            {
            public:
                
                virtual ~IGpsMarkerModule() {}
                virtual IGpsMarkerController& GetGpsMarkerController() = 0;
                virtual GpsMarkerModel& GetGpsMarkerModel() const = 0;
            };
        }
    }
}