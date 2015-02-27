// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class IWorldPinVisibilityStateChangedHandler
            {
            public:
                virtual ~IWorldPinVisibilityStateChangedHandler() { }
                
                virtual void HandlePinBecameFullyVisible() = 0;
                
                virtual void HandlePinBecameFullyInvisible() = 0;
            };
        }
    }
}
