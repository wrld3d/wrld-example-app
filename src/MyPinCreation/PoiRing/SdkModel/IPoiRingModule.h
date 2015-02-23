// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinCreation.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                class IPoiRingModule
                {
                public:
                    virtual ~IPoiRingModule() { }

                    virtual IPoiRingController& GetPoiRingController() const = 0;
                    virtual IPoiRingTouchController& GetPoiRingTouchController() const = 0;


                };
            }
        }
    }
}
