// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace WorldPins
    {
        class IWorldPinsInFocusModel
        {
        public:
            virtual ~IWorldPinsInFocusModel() { }
            
            virtual const std::string& GetTitle() const = 0;
            virtual const std::string& GetSubtitle() const = 0;
            virtual const int GetPinId() const = 0;
        };
    }
}