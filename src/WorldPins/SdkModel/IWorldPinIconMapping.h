// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class IWorldPinIconMapping
            {
            public:
                virtual ~IWorldPinIconMapping() { }

                virtual int IconIndexForKey(const std::string& key) const = 0;
            };
        }
    }
}
