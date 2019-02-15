// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

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

                Eegeo::Routes::Webservice::IRoutingWebservice& GetOfflineRoutingService() override;

            private:
                Webservice::IOfflineRoutingDataParser* m_pOfflineRoutingDataParser;
                Webservice::IOfflineRoutingDataWebService* m_pOfflineRoutingDataWebService;
                OfflineRoutingService* m_pOfflineRoutingService;
                OfflineRoutingController* m_pOfflineRoutingController;
            };
        }
    }
}
