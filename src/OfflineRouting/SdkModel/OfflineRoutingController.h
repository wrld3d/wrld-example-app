// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "OfflineRouting.h"
#include "IOfflineRoutingController.h"
#include "Interiors.h"
#include "ICallback.h"
#include "IAlertBoxFactory.h"
#include "INetworkCapabilities.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"

#include <string>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            class OfflineRoutingController : public IOfflineRoutingController, private Eegeo::NonCopyable
            {
            public:
                OfflineRoutingController(RoutingEngine::IOfflineRoutingEngine& offlineRoutingEngine,
                                         Webservice::IOfflineRoutingDataWebService& dataWebService,
                                         Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                         const Net::SdkModel::INetworkCapabilities& networkCapabilities);

                ~OfflineRoutingController();

                void LoadInteriorData(const Eegeo::Resources::Interiors::InteriorId& interiorId);

                OfflineRoutingInitialisationState GetInitialisationState() const override;

            private:
                void OnVersionsRequestCompleted(const Webservice::OfflineRoutingVersionsRequestResponse& versionsRequestResponse);
                void OnDataRequestCompleted(const Webservice::OfflineRoutingDataRequestResponse& dataRequestResponse);
                void OnFailAlertBoxDismissed();

                bool CanLoadFromInternet();
                void ShowFailureMessage(const std::string& title, const std::string& message);

                RoutingEngine::IOfflineRoutingEngine& m_offlineRoutingEngine;
                Webservice::IOfflineRoutingDataWebService& m_dataWebService;
                Eegeo::UI::NativeAlerts::IAlertBoxFactory& m_alertBoxFactory;
                const Net::SdkModel::INetworkCapabilities& m_networkCapabilities;
                OfflineRoutingInitialisationState m_initialisationState;

                Eegeo::Helpers::TCallback1<OfflineRoutingController, const Webservice::OfflineRoutingVersionsRequestResponse&> m_versionsRequestCompletedCallback;
                Eegeo::Helpers::TCallback1<OfflineRoutingController, const Webservice::OfflineRoutingDataRequestResponse&> m_dataRequestCompletedCallback;
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<OfflineRoutingController> m_failAlertHandler;
            };
        }
    }
}
