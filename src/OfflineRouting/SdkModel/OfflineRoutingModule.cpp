// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OfflineRoutingModule.h"
#include "OfflineRoutingService.h"
#include "OfflineRoutingDataWebService.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            OfflineRoutingModule::OfflineRoutingModule(Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice,
                                                       Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                       const std::string& serviceUrlBase,
                                                       const std::string& apiDevToken,
                                                       const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                m_pOfflineRoutingService = Eegeo_NEW(OfflineRoutingService)(routingWebservice);
                Webservice::OfflineRoutingDataWebService* pTest = Eegeo_NEW(Webservice::OfflineRoutingDataWebService)(webRequestFactory,
                                                                                                                     serviceUrlBase,
                                                                                                                     apiDevToken);

                pTest->RequestVersionsForInterior(interiorId);
                pTest->RequestNavigationDataForInterior(interiorId, "EIM-4c79355e-6fe2-4575-89d9-faf9212cabc3_2019_02_13_15_34_39");
            }

            OfflineRoutingModule::~OfflineRoutingModule()
            {
                Eegeo_DELETE m_pOfflineRoutingService;
            }

            Eegeo::Routes::Webservice::IRoutingWebservice& OfflineRoutingModule::GetOfflineRoutingService()
            {
                return *m_pOfflineRoutingService;
            }
        }
    }
}
