// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkSearchHandler.h"
#include <vector>
#include "StringHelpers.h"
#include "DeepLinkQueryStringParser.h"
#include "QueryData.h"
#include "ICameraTransitionController.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            DeepLinkSearchHandler::DeepLinkSearchHandler(Search::SelectFirstResult::SdkModel::SelectFirstResultSearchService& selectFirstResultSearchService,
                                                         Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                                         Mapscene::SdkModel::MapsceneLoader& mapsceneLoader,
                                                         CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController)
            : m_selectFirstResultSearchService(selectFirstResultSearchService)
            , m_failAlertHandler(this, &DeepLinkSearchHandler::OnFailAlertBoxDismissed)
            , m_mapsceneLoader(mapsceneLoader)
            , m_startupSearchCameraTransitionCompleteCallback(this, &DeepLinkSearchHandler::HandleStartupSearchCameraTransitionComplete)
            , m_cameraTransitionController(cameraTransitionController)
            , m_shouldWaitForTransition(false)
            , m_queryData("",
                          "",
                          "",
                          false,
                          false,
                          false,
                          false)
            {
                m_cameraTransitionController.InsertTransitionCompletedCallback(m_startupSearchCameraTransitionCompleteCallback);
            }
            
            DeepLinkSearchHandler::~DeepLinkSearchHandler()
            {
                m_cameraTransitionController.RemoveTransitionCompletedCallback(m_startupSearchCameraTransitionCompleteCallback);
            }
            
            void DeepLinkSearchHandler::HandleDeepLink(const AppInterface::UrlData& data)
            {
                m_queryData = DeepLinkQueryStringParser().ParseData(data);
                m_shouldWaitForTransition = false;
                if(m_queryData.HasMapscene())
                {
                    m_shouldWaitForTransition = m_queryData.HasQuery();
                    HandleMapscene(data, m_queryData);
                }

                if(m_queryData.HasQuery() && !m_shouldWaitForTransition)
                {
                    m_selectFirstResultSearchService.PerformSearch(m_queryData.GetQuery(),
                                                                   m_queryData.GetIndoorId());
                }
            }
            
            void DeepLinkSearchHandler::HandleMapscene(const AppInterface::UrlData& data, const QueryData& queryData)
            {
                const std::string path = "/" + queryData.GetMapscene();
                m_mapsceneLoader.LoadMapscene(path, true);
            }

            void DeepLinkSearchHandler::HandleStartupSearchCameraTransitionComplete()
            {
                if(m_shouldWaitForTransition)
                {
                    m_shouldWaitForTransition = false;
                    m_selectFirstResultSearchService.PerformSearch(m_queryData.GetQuery(),
                                                                   m_queryData.GetIndoorId());
                }
            }
            
            void DeepLinkSearchHandler::OnFailAlertBoxDismissed()
            { //Do nothing
            }
        }
    }
}

