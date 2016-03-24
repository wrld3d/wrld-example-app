// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Modality.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            class IModalityModule
            {
            public:
                virtual ~IModalityModule() { }

                virtual IModalityModel& GetModalityModel() const = 0;
                virtual IModalityController& GetModalityController() const = 0;
            };
        }
    }
}
