// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinDetailsViewIncludes.h"
#include "MyPinDetails.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            class IMyPinDetailsViewModule
            {
            public:
                virtual ~IMyPinDetailsViewModule() { }

                virtual MyPinDetailsController& GetMyPinDetailsController() const = 0;

                virtual MyPinDetailsView& GetMyPinDetailsView() const = 0;
            };
        }
    }
}
