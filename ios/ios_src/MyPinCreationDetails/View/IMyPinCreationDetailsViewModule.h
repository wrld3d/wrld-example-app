// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinCreationDetailsViewIncludes.h"
#include "MyPinCreationDetails.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            class IMyPinCreationDetailsViewModule
            {
            public:

                virtual ~IMyPinCreationDetailsViewModule() { }

                virtual MyPinCreationDetailsController& GetMyPinCreationDetailsController() const = 0;
                virtual MyPinCreationDetailsView& GetMyPinCreationDetailsView() const = 0;
            };
        }
    }
}
