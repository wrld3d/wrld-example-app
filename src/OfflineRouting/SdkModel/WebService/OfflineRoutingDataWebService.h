// Copyright eeGeo Ltd (2012-2018), All Rights Reserved

#pragma once

#include "Types.h"
#include "OfflineRouting.h"
#include "IOfflineRoutingDataWebService.h"
#include "Interiors.h"
#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"
#include "CallbackCollection.h"

#include <string>
#include <map>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace Webservice
            {
                class OfflineRoutingDataWebService : public IOfflineRoutingDataWebService, private Eegeo::NonCopyable
                {
                public:
                    OfflineRoutingDataWebService(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                 const std::string& serviceUrlBase,
                                                 const std::string& apiDevToken);

                    ~OfflineRoutingDataWebService() {}

                    OfflineRoutingWebserviceRequestId RequestVersionsForInterior(const Eegeo::Resources::Interiors::InteriorId& indoorId);

                    OfflineRoutingWebserviceRequestId RequestNavigationDataForInterior(const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                                                       const std::string& buildId);
                    void CancelRequest(OfflineRoutingWebserviceRequestId requestId);

                    void RegisterVersionsRequestCompletedCallback(OfflineRoutingVersionsRequestCompletedCallback& callback);
                    void UnregisterVersionsRequestCompletedCallback(OfflineRoutingVersionsRequestCompletedCallback& callback);

                    void RegisterDataRequestCompletedCallback(OfflineRoutingDataRequestCompletedCallback& callback);
                    void UnregisterDataRequestCompletedCallback(OfflineRoutingDataRequestCompletedCallback& callback);

                private:
                    void OnRequestComplete(Eegeo::Web::IWebResponse& webResponse);
                    OfflineRoutingWebserviceRequestId NextRequestId();

                    void NotifyVersionsRequestCompleted(OfflineRoutingWebserviceRequestId requestId,
                                                        bool requestSucceeded,
                                                        const std::string& responseString);
                    void NotifyDataRequestCompleted(OfflineRoutingWebserviceRequestId requestId,
                                                    bool requestSucceeded,
                                                    const std::string& responseString);

                    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;

                    std::map<OfflineRoutingWebserviceRequestId, Eegeo::Web::IWebLoadRequest*> m_webRequests;
                    Eegeo::Web::TWebLoadRequestCompletionCallback<OfflineRoutingDataWebService> m_webLoadFinishedHandler;
                    Eegeo::Helpers::CallbackCollection1<const OfflineRoutingVersionsRequestResponse> m_versionsRequestCompletedCallbacks;
                    Eegeo::Helpers::CallbackCollection1<const OfflineRoutingDataRequestResponse> m_dataRequestCompletedCallbacks;

                    const std::string m_serviceUrlBase;
                    const std::string m_apiDevToken;
                    OfflineRoutingWebserviceRequestId m_nextId;
                };
            }
        }
    }
}
