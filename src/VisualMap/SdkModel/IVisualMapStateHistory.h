// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VisualMap.h"

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            class IVisualMapStateHistory
            {
            public:
                virtual ~IVisualMapStateHistory() {}
                
                virtual void Push(const VisualMapState& visualMapState) = 0;
                virtual VisualMapState Pop() = 0;
            };
        }
    }
}