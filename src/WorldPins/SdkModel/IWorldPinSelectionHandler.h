// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class IWorldPinSelectionHandler
            {
            public:
                virtual ~IWorldPinSelectionHandler() { }

                virtual void SelectPin() = 0;
            };
        }
    }
}
