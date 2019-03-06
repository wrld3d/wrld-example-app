// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingModule.h"
#include "OfflineRoutingService.h"
#include "OfflineRoutingServiceRouteDataBuilder.h"
#include "OfflineRoutingDataParser.h"
#include "OfflineRoutingDataWebService.h"
#include "OfflineRoutingController.h"
#include "OfflineRoutingDataBuilder.h"
#include "OfflineRoutingDataRepository.h"
#include "OfflineRoutingGraphPositioner.h"
#include "OfflineRoutingPathFinder.h"
#include "OfflineRoutingEngine.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            OfflineRoutingModule::OfflineRoutingModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                       Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                                       const Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                       const std::string& serviceUrlBase,
                                                       const std::string& apiDevToken,
                                                       const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                m_pOfflineRoutingDataParser = Eegeo_NEW(Webservice::OfflineRoutingDataParser)();
                m_pOfflineRoutingDataWebService = Eegeo_NEW(Webservice::OfflineRoutingDataWebService)(webRequestFactory,
                                                                                                      *m_pOfflineRoutingDataParser,
                                                                                                      serviceUrlBase,
                                                                                                      apiDevToken);

                m_pOfflineRoutingDataSearchService = Eegeo_NEW(RoutingEngine::OfflineRoutingDataSearchService)();
                m_pOfflineRoutingDataRepository = Eegeo_NEW(RoutingEngine::OfflineRoutingDataRepository)(*m_pOfflineRoutingDataSearchService);
                m_pOfflineRoutingDataBuilder = Eegeo_NEW(RoutingEngine::OfflineRoutingDataBuilder)();
                m_pOfflineRoutingGraphPositioner = Eegeo_NEW(RoutingEngine::OfflineRoutingGraphPositioner)(*m_pOfflineRoutingDataRepository);
                m_pOfflineRoutingPathFinder = Eegeo_NEW(RoutingEngine::OfflineRoutingPathFinder)(*m_pOfflineRoutingDataRepository);
                m_pOfflineRoutingEngine = Eegeo_NEW(RoutingEngine::OfflineRoutingEngine)(*m_pOfflineRoutingDataRepository,
                                                                                         *m_pOfflineRoutingDataBuilder);

                m_pOfflineRoutingServiceRouteDataBuilder = Eegeo_NEW(OfflineRoutingServiceRouteDataBuilder)(*m_pOfflineRoutingDataRepository);
                m_pOfflineRoutingService = Eegeo_NEW(OfflineRoutingService)(*m_pOfflineRoutingGraphPositioner,
                                                                            *m_pOfflineRoutingPathFinder,
                                                                            *m_pOfflineRoutingServiceRouteDataBuilder);

                m_pOfflineRoutingController = Eegeo_NEW(OfflineRoutingController)(*m_pOfflineRoutingEngine,
                                                                                  *m_pOfflineRoutingDataWebService,
                                                                                  alertBoxFactory,
                                                                                  networkCapabilities);

                m_pOfflineRoutingController->LoadInteriorData(interiorId);
            }

            OfflineRoutingModule::~OfflineRoutingModule()
            {
                Eegeo_DELETE m_pOfflineRoutingController;
                Eegeo_DELETE m_pOfflineRoutingService;
                Eegeo_DELETE m_pOfflineRoutingServiceRouteDataBuilder;
                Eegeo_DELETE m_pOfflineRoutingEngine;
                Eegeo_DELETE m_pOfflineRoutingPathFinder;
                Eegeo_DELETE m_pOfflineRoutingGraphPositioner;
                Eegeo_DELETE m_pOfflineRoutingDataBuilder;
                Eegeo_DELETE m_pOfflineRoutingDataRepository;
                Eegeo_DELETE m_pOfflineRoutingDataSearchService;
                Eegeo_DELETE m_pOfflineRoutingDataWebService;
                Eegeo_DELETE m_pOfflineRoutingDataParser;
            }

            Eegeo::Routes::Webservice::IRoutingWebservice& OfflineRoutingModule::GetOfflineRoutingService()
            {
                return *m_pOfflineRoutingService;
            }

            const IOfflineRoutingController& OfflineRoutingModule::GetOfflineRoutingController() const
            {
                return *m_pOfflineRoutingController;
            }

            void OfflineRoutingModule::Update(float dt)
            {
                m_pOfflineRoutingService->Update(dt);
            }
        }
    }
}
