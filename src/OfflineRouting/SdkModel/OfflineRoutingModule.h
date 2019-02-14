// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "OfflineRouting.h"
#include "IOfflineRoutingModule.h"
#include "IRoutingWebservice.h"
#include "Web.h"
#include "Interiors.h"

#include <string>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            class OfflineRoutingModule : public IOfflineRoutingModule, private Eegeo::NonCopyable
            {
            public:
                OfflineRoutingModule(Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice,
                                     Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                     const std::string& serviceUrlBase,
                                     const std::string& apiDevToken,
                                     const Eegeo::Resources::Interiors::InteriorId& interiorId);

                ~OfflineRoutingModule();

                Eegeo::Routes::Webservice::IRoutingWebservice& GetOfflineRoutingService();

            private:
                Eegeo::Routes::Webservice::IRoutingWebservice* m_pOfflineRoutingService;
            };
        }
    }
}
