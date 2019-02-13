// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OfflineRoutingModule.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            OfflineRoutingModule::OfflineRoutingModule(Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice)
            : m_routingWebservice(routingWebservice)
            {
            }

            Eegeo::Routes::Webservice::IRoutingWebservice& OfflineRoutingModule::GetOfflineRoutingService()
            {
                return m_routingWebservice;
            }
        }
    }
}
