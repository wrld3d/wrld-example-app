// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

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
                                                 IOfflineRoutingDataParser& dataParser,
                                                 const std::string& serviceUrlBase,
                                                 const std::string& apiDevToken);

                    ~OfflineRoutingDataWebService() {}

                    OfflineRoutingWebserviceRequestId RequestVersionsForInterior(const Eegeo::Resources::Interiors::InteriorId& indoorId) override;

                    OfflineRoutingWebserviceRequestId RequestNavigationDataForInterior(const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                                                       const std::string& buildId) override;
                    void CancelRequest(OfflineRoutingWebserviceRequestId requestId) override;

                    void RegisterVersionsRequestCompletedCallback(OfflineRoutingVersionsRequestCompletedCallback& callback) override;
                    void UnregisterVersionsRequestCompletedCallback(OfflineRoutingVersionsRequestCompletedCallback& callback) override;

                    void RegisterDataRequestCompletedCallback(OfflineRoutingDataRequestCompletedCallback& callback) override;
                    void UnregisterDataRequestCompletedCallback(OfflineRoutingDataRequestCompletedCallback& callback) override;

                private:
                    void OnRequestComplete(Eegeo::Web::IWebResponse& webResponse);
                    OfflineRoutingWebserviceRequestId NextRequestId();

                    void NotifyVersionsRequestCompleted(OfflineRoutingWebserviceRequestId requestId,
                                                        const Eegeo::Resources::Interiors::InteriorId& requestInteriorId,
                                                        const std::string& responseString);
                    void NotifyDataRequestCompleted(OfflineRoutingWebserviceRequestId requestId,
                                                    const Eegeo::Resources::Interiors::InteriorId& requestInteriorId,
                                                    const std::string& requestBuildId,
                                                    const std::string& responseString);

                    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                    IOfflineRoutingDataParser& m_dataParser;

                    std::map<OfflineRoutingWebserviceRequestId, Eegeo::Web::IWebLoadRequest*> m_webRequests;
                    Eegeo::Web::TWebLoadRequestCompletionCallback<OfflineRoutingDataWebService> m_webLoadFinishedHandler;
                    Eegeo::Helpers::CallbackCollection1<const OfflineRoutingVersionsRequestResponse&> m_versionsRequestCompletedCallbacks;
                    Eegeo::Helpers::CallbackCollection1<const OfflineRoutingDataRequestResponse&> m_dataRequestCompletedCallbacks;

                    const std::string m_serviceUrlBase;
                    const std::string m_apiDevToken;
                    OfflineRoutingWebserviceRequestId m_nextId;
                };
            }
        }
    }
}
