// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "OfflineRouting.h"
#include "Interiors.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            class OfflineRoutingController : private Eegeo::NonCopyable
            {
            public:
                OfflineRoutingController(Webservice::IOfflineRoutingDataWebService& dataWebService);

                ~OfflineRoutingController();

                void LoadInteriorData(const Eegeo::Resources::Interiors::InteriorId& interiorId);

            private:
                void OnVersionsRequestCompleted(const Webservice::OfflineRoutingVersionsRequestResponse& versionsRequestResponse);
                void OnDataRequestCompleted(const Webservice::OfflineRoutingDataRequestResponse& dataRequestResponse);

                Webservice::IOfflineRoutingDataWebService& m_dataWebService;

                Eegeo::Helpers::TCallback1<OfflineRoutingController, const Webservice::OfflineRoutingVersionsRequestResponse&> m_versionsRequestCompletedCallback;
                Eegeo::Helpers::TCallback1<OfflineRoutingController, const Webservice::OfflineRoutingDataRequestResponse&> m_dataRequestCompletedCallback;
            };
        }
    }
}
