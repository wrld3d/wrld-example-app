// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VisualMap.h"

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            class IVisualMapModule
            {
            public:
                virtual ~IVisualMapModule(){}
                
                virtual IVisualMapService& GetVisualMapService() const = 0;
            };
        }
    }
}