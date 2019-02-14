// Copyright eeGeo Ltd (2012-2018), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "Interiors.h"

#include <string>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace Webservice
            {
                class IOfflineRoutingDataWebService
                {
                public:
                    
                    virtual ~IOfflineRoutingDataWebService() {}


                    virtual OfflineRoutingWebserviceRequestId RequestVersionsForInterior(const Eegeo::Resources::Interiors::InteriorId& indoorId) = 0;
                    virtual OfflineRoutingWebserviceRequestId RequestNavigationDataForInterior(const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                                                               const std::string& buildId) = 0;
                    
                    virtual void CancelRequest(OfflineRoutingWebserviceRequestId requestId) = 0;

                    virtual void RegisterVersionsRequestCompletedCallback(OfflineRoutingVersionsRequestCompletedCallback& callback) = 0;
                    virtual void UnregisterVersionsRequestCompletedCallback(OfflineRoutingVersionsRequestCompletedCallback& callback) = 0;
                    
                    virtual void RegisterDataRequestCompletedCallback(OfflineRoutingDataRequestCompletedCallback& callback) = 0;
                    virtual void UnregisterDataRequestCompletedCallback(OfflineRoutingDataRequestCompletedCallback& callback) = 0;
                };
            }
        }
    }
}
