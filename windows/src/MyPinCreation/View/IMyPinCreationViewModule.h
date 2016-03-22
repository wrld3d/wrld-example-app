// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include "IMyPinCreationInitiationView.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class IMyPinCreationViewModule
            {
            public:
                virtual ~IMyPinCreationViewModule() { }
                virtual IMyPinCreationInitiationView& GetMyPinCreationInitiationView() = 0;
            };
        }
    }
}
