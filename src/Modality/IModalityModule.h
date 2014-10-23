// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Modality.h"

namespace ExampleApp
{
    namespace Modality
    {
        class IModalityModule
        {
        public:
            virtual ~IModalityModule() { }
            
            virtual IModalityModel& GetModalityModel() const = 0;
        };
    }
}
