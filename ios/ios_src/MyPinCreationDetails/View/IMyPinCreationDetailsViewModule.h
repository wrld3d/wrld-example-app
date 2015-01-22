// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinCreationDetailsViewIncludes.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        class IMyPinCreationDetailsViewModule
        {
        public:
            
            virtual ~IMyPinCreationDetailsViewModule() { }
            
            virtual MyPinCreationDetailsViewController& GetMyPinCreationDetailsViewController() const = 0;
            virtual MyPinCreationDetailsView& GetMyPinCreationDetailsView() const = 0;
        };
    }
}