// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            namespace WorldPinVisibility
            {
                enum Values
                {
                    World = 0x01,
                    Search = 0x02,
                    TourPin = 0x04,
                    UserPin = 0x08,
                    
                    All = ~0,
                    None = 0
                };
            }
        }
    }
}