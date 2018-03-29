// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "RouteData.h"

#include <vector>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingModule;
            class NavRouteDrawingController;
            class NavRoutingServiceController;
            
            typedef Eegeo::Helpers::ICallback1<const std::vector<Eegeo::Routes::Webservice::RouteData>> RoutesReceivedCallback;
        }
    }
}
