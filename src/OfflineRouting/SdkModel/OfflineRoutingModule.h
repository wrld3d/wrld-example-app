// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "OfflineRouting.h"
#include "IOfflineRoutingModule.h"
#include "IRoutingWebservice.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            class OfflineRoutingModule : public IOfflineRoutingModule, private Eegeo::NonCopyable
            {
            public:
                OfflineRoutingModule(Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice);

                ~OfflineRoutingModule() {}

                Eegeo::Routes::Webservice::IRoutingWebservice& GetOfflineRoutingService();

            private:

                Eegeo::Routes::Webservice::IRoutingWebservice& m_routingWebservice;
            };
        }
    }
}
