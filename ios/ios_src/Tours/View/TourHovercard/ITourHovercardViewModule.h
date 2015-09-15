// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "TourHovercardViewIncludes.h"
#include "WorldPins.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourHovercard
            {
                class ITourHovercardViewModule
                {
                public:
                    virtual ~ITourHovercardViewModule() { }
                    
                    virtual WorldPins::View::WorldPinOnMapController& GetWorldPinOnMapController() const = 0;
                    
                    virtual TourHovercardView& GetTourHovercardView() const = 0;
                    
                    virtual ITourHovercardView& GetTourHovercardViewInterop() const = 0;
                };
            }
        }
    }
}