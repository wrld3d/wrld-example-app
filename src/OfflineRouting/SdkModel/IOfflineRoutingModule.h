// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "IRoutingWebservice.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            class IOfflineRoutingModule
            {
            public:

                virtual ~IOfflineRoutingModule() {}
                
                virtual Eegeo::Routes::Webservice::IRoutingWebservice& GetOfflineRoutingService() = 0;
            };
        }
    }
}
