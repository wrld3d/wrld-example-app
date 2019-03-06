// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            class IOfflineRoutingController
            {
            public:
                virtual ~IOfflineRoutingController() {}

                virtual OfflineRoutingInitialisationState GetInitialisationState() const = 0;
            };
        }
    }
}
