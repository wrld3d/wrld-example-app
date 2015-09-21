// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "TourFullScreenImageViewIncludes.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                class ITourFullScreenImageViewModule
                {
                public:
                    virtual ~ITourFullScreenImageViewModule() { }
                    
                    virtual TourFullScreenImageView& GetTourFullScreenImageView() const = 0;
                };
            }
        }
    }
}
