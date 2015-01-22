// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinCreation.h"
#include "MyPinCreationInitiationViewIncludes.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class IMyPinCreationInitiationViewModule
            {
            public:

                virtual ~IMyPinCreationInitiationViewModule() { }

                virtual MyPinCreationInitiationController& GetMyPinCreationInitiationController() const = 0;
                virtual MyPinCreationInitiationView& GetMyPinCreationInitiationView() const = 0;
            };
        }
    }
}
