// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "TourWebViewIncludes.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourWeb
            {
                class ITourWebViewModule
                {
                public:
                    
                    virtual ~ITourWebViewModule() { }
                    
                    virtual TourWebView& GetTourWebView() const = 0;
                };

            }
        }
    }
}