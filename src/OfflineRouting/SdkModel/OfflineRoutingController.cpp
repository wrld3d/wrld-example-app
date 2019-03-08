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
                                                               Webservice::IOfflineRoutingDataWebService& dataWebService,
                                                               Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                                               const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                               const Net::SdkModel::INetworkCapabilities& networkCapabilities)
            : m_offlineRoutingEngine(offlineRoutingEngine)
            , m_dataWebService(dataWebService)
            , m_alertBoxFactory(alertBoxFactory)
            , m_networkCapabilities(networkCapabilities)
            , m_initialisationState(OfflineRoutingInitialisationState::Initialising)
            , m_versionsRequestCompletedCallback(this, &OfflineRoutingController::OnVersionsRequestCompleted)
            , m_dataRequestCompletedCallback(this, &OfflineRoutingController::OnDataRequestCompleted)
            , m_failAlertHandler(this, &OfflineRoutingController::OnFailAlertBoxDismissed)
            {
                m_dataWebService.RegisterVersionsRequestCompletedCallback(m_versionsRequestCompletedCallback);
                m_dataWebService.RegisterDataRequestCompletedCallback(m_dataRequestCompletedCallback);

                LoadInteriorData(interiorId);
            }

            OfflineRoutingController::~OfflineRoutingController()
            {
                m_dataWebService.UnregisterDataRequestCompletedCallback(m_dataRequestCompletedCallback);
                m_dataWebService.UnregisterVersionsRequestCompletedCallback(m_versionsRequestCompletedCallback);
            }

            void OfflineRoutingController::LoadInteriorData(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                if (!interiorId.IsValid())
                {
                    m_initialisationState = InitialisationFailed;
                    return;
                }

                if (CanLoadFromInternet())
                {
                    m_dataWebService.RequestVersionsForInterior(interiorId);
                    return;
                }

                if (m_offlineRoutingEngine.TryLoadDataFromStorage(interiorId))
                {
                    m_initialisationState = Ready;
                }
                else
                {
                    m_initialisationState = InitialisationFailed;
                }
            }

            OfflineRoutingInitialisationState OfflineRoutingController::GetInitialisationState() const
            {
                return m_initialisationState;
            }

            void OfflineRoutingController::OnVersionsRequestCompleted(const Webservice::OfflineRoutingVersionsRequestResponse& versionsRequestResponse)
            {
                if (!versionsRequestResponse.succeeded)
                {
                    ShowFailureMessage("Version request failed", "Unable to get interior versions from service. Navigation functionality is disabled. Please restart application to load required data.");
                    return;
                }

                Webservice::OfflineRoutingIndoorVersion latestVersion;
                if (!TryGetLatestVersion(versionsRequestResponse.results, latestVersion))
                {
                    ShowFailureMessage("Version request failed", "No valid navigation data available for the specified indoor map. Navigation functionality is disabled. Please restart application to load required data.");
                    return;
                }

                std::string localBuildId;
                if (m_offlineRoutingEngine.TryGetLocalBuildIdForInterior(versionsRequestResponse.interiorId, localBuildId))
                {
                    if (localBuildId == latestVersion.buildId)
                    {
                        if (m_offlineRoutingEngine.TryLoadDataFromStorage(versionsRequestResponse.interiorId))
                        {
                            m_initialisationState = Ready;
                            return;
                        }
                    }
                }

                m_dataWebService.RequestNavigationDataForInterior(versionsRequestResponse.interiorId, latestVersion.buildId);
            }

            void OfflineRoutingController::OnDataRequestCompleted(const Webservice::OfflineRoutingDataRequestResponse& dataRequestResponse)
            {
                if (!dataRequestResponse.succeeded)
                {
                    ShowFailureMessage("Data request failed", "Unable to get navigation data from service. Navigation functionality is disabled. Please restart application to load required data.");
                    return;
                }

                m_offlineRoutingEngine.LoadGraphFromNavigationData(dataRequestResponse.interiorId,
                                                                   dataRequestResponse.buildId,
                                                                   dataRequestResponse.floorData,
                                                                   dataRequestResponse.multiFloorData);
                m_initialisationState = Ready;
            }

            void OfflineRoutingController::OnFailAlertBoxDismissed()
            {
                m_initialisationState = InitialisationFailed;
            }

            bool OfflineRoutingController::CanLoadFromInternet()
            {
                const bool dontRequireWifi = !m_networkCapabilities.StreamOverWifiOnly();
                const bool haveWifi = m_networkCapabilities.ConnectedToWifi();
                const bool haveNetwork = m_networkCapabilities.NetworkAvailable();

                return haveWifi || (haveNetwork && dontRequireWifi);
            }

            void OfflineRoutingController::ShowFailureMessage(const std::string& title, const std::string& message)
            {
                m_alertBoxFactory.CreateSingleOptionAlertBox(title,
                                                             message,
                                                             m_failAlertHandler);
            }
        }
    }
}
