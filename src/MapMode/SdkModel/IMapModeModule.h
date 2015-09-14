// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MapMode.h"
#include "IMapModeModel.h"

namespace ExampleApp
{
    namespace MapMode
    {
        namespace SdkModel
        {
            class IMapModeModule
            {
            public:
                virtual ~IMapModeModule()
                {

                }

                virtual IMapModeModel& GetMapModeModel() = 0;
            };
        }
    }
}