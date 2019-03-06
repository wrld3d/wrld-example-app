// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "OfflineRouting.h"
#include "IOfflineRoutingModule.h"
#include "Web.h"
#include "Interiors.h"
#include "OfflineRoutingDataSearchService.h"
#include "IAlertBoxFactory.h"
#include "INetworkCapabilities.h"

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
                OfflineRoutingModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                     Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                     const Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                     const std::string& serviceUrlBase,
                                     const std::string& apiDevToken,
                                     const Eegeo::Resources::Interiors::InteriorId& interiorId);

                ~OfflineRoutingModule();

                Eegeo::Routes::Webservice::IRoutingWebservice& GetOfflineRoutingService() override;

                const IOfflineRoutingController& GetOfflineRoutingController() const override;

                void Update(float dt) override;

            private:
                Webservice::IOfflineRoutingDataParser* m_pOfflineRoutingDataParser;
                Webservice::IOfflineRoutingDataWebService* m_pOfflineRoutingDataWebService;

                RoutingEngine::OfflineRoutingDataSearchService* m_pOfflineRoutingDataSearchService;
                RoutingEngine::IOfflineRoutingDataRepository* m_pOfflineRoutingDataRepository;
                RoutingEngine::IOfflineRoutingDataBuilder* m_pOfflineRoutingDataBuilder;
                RoutingEngine::IOfflineRoutingGraphPositioner* m_pOfflineRoutingGraphPositioner;
                RoutingEngine::IOfflineRoutingPathFinder* m_pOfflineRoutingPathFinder;
                RoutingEngine::IOfflineRoutingEngine* m_pOfflineRoutingEngine;

                IOfflineRoutingServiceRouteDataBuilder* m_pOfflineRoutingServiceRouteDataBuilder;
                OfflineRoutingService* m_pOfflineRoutingService;
                OfflineRoutingController* m_pOfflineRoutingController;
            };
        }
    }
}
