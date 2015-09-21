// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Tours.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                class ITourFullScreenImageView
                {
                public:
                    virtual ~ITourFullScreenImageView() { }
                    
                    virtual void BeginCeremony(const std::string& asset,
                                               const std::string& message) = 0;
                    
                    virtual void EndCeremony() = 0;
                };
            }
        }
    }
}
