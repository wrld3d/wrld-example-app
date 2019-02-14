// Copyright eeGeo Ltd (2012-2018), All Rights Reserved

#include "OfflineRoutingDataWebService.h"
#include "InteriorId.h"
#include "IWebLoadRequest.h"
#include "IWebLoadRequestFactory.h"

#include <sstream>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace Webservice
            {
                namespace
                {
                    enum WebRequestType
                    {
                        VersionsRequest,
                        NavigationDataRequest
                    };

                    struct WebRequestUserData
                    {
                        OfflineRoutingWebserviceRequestId Id;
                        WebRequestType Type;

                        WebRequestUserData(OfflineRoutingWebserviceRequestId id, WebRequestType type)
                        : Id(id)
                        , Type(type)
                        {
                        }
                    };
                }

                OfflineRoutingDataWebService::OfflineRoutingDataWebService(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                           const std::string& serviceUrlBase,
                                                                           const std::string& apiDevToken)
                : m_webRequestFactory(webRequestFactory)
                , m_apiDevToken(apiDevToken)
                , m_webLoadFinishedHandler(this, &OfflineRoutingDataWebService::OnRequestComplete)
                , m_serviceUrlBase(serviceUrlBase)
                , m_nextId(1)
                {

                }

                OfflineRoutingWebserviceRequestId OfflineRoutingDataWebService::RequestVersionsForInterior(const Eegeo::Resources::Interiors::InteriorId& indoorId)
                {
                    Eegeo_ASSERT(indoorId.IsValid());
                    auto requestId = NextRequestId();

                    WebRequestUserData* pUserData = Eegeo_NEW(WebRequestUserData)(requestId, WebRequestType::VersionsRequest);

                    std::stringstream ss;
                    ss << m_serviceUrlBase << "indoor-maps/" << indoorId.Value() << "/versions/";
                    ss << "?token=" << m_apiDevToken;

                    auto url = ss.str();

                    auto* pRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, url, m_webLoadFinishedHandler)
                            .SetUserData((void*)pUserData)
                            .Build();

                    m_webRequests.insert({ requestId, pRequest });

                    pRequest->Load();

                    return requestId;
                }

                OfflineRoutingWebserviceRequestId OfflineRoutingDataWebService::RequestNavigationDataForInterior(const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                                                                           const std::string& buildId)
                {
                    Eegeo_ASSERT(indoorId.IsValid());
                    Eegeo_ASSERT(!buildId.empty());
                    auto requestId = NextRequestId();

                    WebRequestUserData* pUserData = Eegeo_NEW(WebRequestUserData)(requestId, WebRequestType::NavigationDataRequest);

                    std::stringstream ss;
                    ss << m_serviceUrlBase << "indoor-maps/" << indoorId.Value() << "/versions/" << buildId << "/navigation-data";
                    ss << "?token=" << m_apiDevToken;

                    auto url = ss.str();

                    auto* pRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, url, m_webLoadFinishedHandler)
                            .SetUserData((void*)pUserData)
                            .Build();

                    m_webRequests.insert({ requestId, pRequest });

                    pRequest->Load();

                    return requestId;
                }

                void OfflineRoutingDataWebService::CancelRequest(OfflineRoutingWebserviceRequestId requestId)
                {
                    auto entry = m_webRequests.find(requestId);
                    if (entry != m_webRequests.end())
                    {
                        auto* pRequest = entry->second;
                        WebRequestUserData* pUserData(static_cast<WebRequestUserData*>(pRequest->GetUserData()));
                        Eegeo_DELETE pUserData;
                        pRequest->Cancel();
                        m_webRequests.erase(entry);
                    }
                }

                void OfflineRoutingDataWebService::RegisterVersionsRequestCompletedCallback(OfflineRoutingVersionsRequestCompletedCallback& callback)
                {
                    m_versionsRequestCompletedCallbacks.AddCallback(callback);
                }

                void OfflineRoutingDataWebService::UnregisterVersionsRequestCompletedCallback(OfflineRoutingVersionsRequestCompletedCallback& callback)
                {
                    m_versionsRequestCompletedCallbacks.RemoveCallback(callback);
                }

                void OfflineRoutingDataWebService::RegisterDataRequestCompletedCallback(OfflineRoutingDataRequestCompletedCallback& callback)
                {
                    m_dataRequestCompletedCallbacks.AddCallback(callback);
                }

                void OfflineRoutingDataWebService::UnregisterDataRequestCompletedCallback(OfflineRoutingDataRequestCompletedCallback& callback)
                {
                    m_dataRequestCompletedCallbacks.RemoveCallback(callback);
                }

                void OfflineRoutingDataWebService::OnRequestComplete(Eegeo::Web::IWebResponse& webResponse)
                {
                    if (webResponse.IsCancelled())
                    {
                        return;
                    }

                    bool requestSucceeded = webResponse.IsSucceeded() && webResponse.GetHttpStatusCode() == 200;

                    WebRequestUserData* pUserData(static_cast<WebRequestUserData*>(webResponse.GetUserData()));

                    OfflineRoutingWebserviceRequestId requestId = pUserData->Id;
                    WebRequestType requestType = pUserData->Type;
                    Eegeo_DELETE pUserData;

                    std::string responseString;

                    if (requestSucceeded)
                    {
                        const auto& bodyData = webResponse.GetBodyData();
                        size_t resultSize = bodyData.size();
                        responseString = std::string(reinterpret_cast<char const*>(&(bodyData.front())), resultSize);
                    }

                    switch (requestType)
                    {
                        case WebRequestType::VersionsRequest:
                            NotifyVersionsRequestCompleted(requestId, requestSucceeded, responseString);
                            break;
                        case WebRequestType::NavigationDataRequest:
                            NotifyDataRequestCompleted(requestId, requestSucceeded, responseString);
                            break;
                    }

                    m_webRequests.erase(requestId);
                }

                void OfflineRoutingDataWebService::NotifyVersionsRequestCompleted(OfflineRoutingWebserviceRequestId requestId,
                                                                                  bool requestSucceeded,
                                                                                  const std::string& responseString)
                {
                    //TODO parse
                    //TODO callback
                }

                void OfflineRoutingDataWebService::NotifyDataRequestCompleted(OfflineRoutingWebserviceRequestId requestId,
                                                                              bool requestSucceeded,
                                                                              const std::string& responseString)
                {
                    //TODO parse
                    //TODO callback
                }

                OfflineRoutingWebserviceRequestId OfflineRoutingDataWebService::NextRequestId()
                {
                    return m_nextId++;
                }
            }
        }
    }
}