// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingController.h"
#include "IOfflineRoutingEngine.h"
#include "IOfflineRoutingDataWebService.h"
#include "OfflineRoutingIndoorVersion.h"
#include "OfflineRoutingDataRequestResponse.h"
#include "OfflineRoutingVersionsRequestResponse.h"

#include <string>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace
            {
                const std::string SuccessfulBuildStatus = "CompilationSucceeded";

                bool TryGetLatestVersion(const std::vector<Webservice::OfflineRoutingIndoorVersion>& versions, Webservice::OfflineRoutingIndoorVersion& out_latestVersion)
                {
                    bool foundVersion = false;

                    for (const auto& version: versions)
                    {
                        if (version.buildStatus != SuccessfulBuildStatus)
                        {
                            continue;
                        }

                        if (foundVersion)
                        {
                            if (out_latestVersion.createdAt < version.createdAt)
                            {
                                out_latestVersion = version;
                            }
                        }
                        else
                        {
                            out_latestVersion = version;
                            foundVersion = true;
                        }
                    }

                    return foundVersion;
                }
            }

            OfflineRoutingController::OfflineRoutingController(RoutingEngine::IOfflineRoutingEngine& offlineRoutingEngine,
                                                               Webservice::IOfflineRoutingDataWebService& dataWebService)
            : m_offlineRoutingEngine(offlineRoutingEngine)
            , m_dataWebService(dataWebService)
            , m_versionsRequestCompletedCallback(this, &OfflineRoutingController::OnVersionsRequestCompleted)
            , m_dataRequestCompletedCallback(this, &OfflineRoutingController::OnDataRequestCompleted)
            {
                m_dataWebService.RegisterVersionsRequestCompletedCallback(m_versionsRequestCompletedCallback);
                m_dataWebService.RegisterDataRequestCompletedCallback(m_dataRequestCompletedCallback);
            }

            OfflineRoutingController::~OfflineRoutingController()
            {
                m_dataWebService.UnregisterDataRequestCompletedCallback(m_dataRequestCompletedCallback);
                m_dataWebService.UnregisterVersionsRequestCompletedCallback(m_versionsRequestCompletedCallback);
            }

            void OfflineRoutingController::LoadInteriorData(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                m_dataWebService.RequestVersionsForInterior(interiorId);
            }

            void OfflineRoutingController::OnVersionsRequestCompleted(const Webservice::OfflineRoutingVersionsRequestResponse& versionsRequestResponse)
            {
                Webservice::OfflineRoutingIndoorVersion latestVersion;
                if (TryGetLatestVersion(versionsRequestResponse.results, latestVersion))
                {
                    bool shouldLoadData = true;
                    std::string localBuildId;
                    if (m_offlineRoutingEngine.TryGetLocalBuildIdForInterior(versionsRequestResponse.interiorId, localBuildId))
                    {
                        if (localBuildId == latestVersion.buildId)
                        {
                            shouldLoadData = false;
                        }
                    }

                    if (shouldLoadData)
                    {
                        m_dataWebService.RequestNavigationDataForInterior(versionsRequestResponse.interiorId, latestVersion.buildId);
                    }

                }
            }

            void OfflineRoutingController::OnDataRequestCompleted(const Webservice::OfflineRoutingDataRequestResponse& dataRequestResponse)
            {
                m_offlineRoutingEngine.LoadGraphFromNavigationData(dataRequestResponse.interiorId,
                                                                   dataRequestResponse.buildId,
                                                                   dataRequestResponse.floorData,
                                                                   dataRequestResponse.multiFloorData);
            }
        }
    }
}
