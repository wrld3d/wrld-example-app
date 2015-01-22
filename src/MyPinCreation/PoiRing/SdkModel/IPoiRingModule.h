// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinCreation.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            class IPoiRingModule
            {
            public:
                virtual ~IPoiRingModule(){ }
                
                virtual IPoiRingController& GetPoiRingController() const = 0;
                virtual IPoiRingTouchController& GetPoiRingTouchController() const = 0;

                
            };
        }
    }
}