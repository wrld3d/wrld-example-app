// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CameraTransitionController.h"
#include "EcefTangentBasis.h"
#include "GpsGlobeCameraController.h"
#include "CameraHelpers.h"
#include "MathFunc.h"
#include "EarthConstants.h"
#include "Quaternion.h"
#include "NavigationService.h"
#include "TerrainHeightProvider.h"
#include "InteriorsExplorerCameraController.h"
#include "IAppModeModel.h"
#include "InteriorSelectionModel.h"
#include "TransitionToWorldPointStage.h"
#include "ExitCurrentInteriorStage.h"
#include "TransitionToInteriorStage.h"
#include "CameraTransitionChangedMessage.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            CameraTransitionController::CameraTransitionController(Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController,
                                                                   ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& interiorsCameraController,
                                                                   Eegeo::Location::NavigationService& navigationService,
                                                                   Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                                                   ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                   Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                   Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                   InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                                   ExampleApp::ExampleAppMessaging::TMessageBus& messageBus)
            : m_cameraController(cameraController)
            , m_interiorsCameraController(interiorsCameraController)
            , m_navigationService(navigationService)
            , m_terrainHeightProvider(terrainHeightProvider)
            , m_appModeModel(appModeModel)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorController(interiorController)
            , m_interiorsExplorerModel(interiorsExplorerModel)
            , m_isTransitioning(false)
            , m_defaultInteriorId(Eegeo::Resources::Interiors::InteriorId::NullId())
            , m_messageBus(messageBus)
            {

            }
            
            void CameraTransitionController::StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                                               float distanceFromInterest,
                                                               bool jumpIfFar)
            {
                const Eegeo::Space::EcefTangentBasis& cameraInterestBasis = m_cameraController.GetInterestBasis();
                
                float bearingRadians = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(cameraInterestBasis.GetPointEcef(),
                                                                                               cameraInterestBasis.GetForward());
                
                StartTransitionTo(newInterestPoint, distanceFromInterest, bearingRadians, m_defaultInteriorId, 0, jumpIfFar);
            }
            
            void CameraTransitionController::StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                                               float distanceFromInterest,
                                                               float newHeadingRadians,
                                                               bool jumpIfFar)
            {
                StartTransitionTo(newInterestPoint, distanceFromInterest, newHeadingRadians, m_defaultInteriorId, 0, jumpIfFar);
            }
            
            void CameraTransitionController::StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                                               float distanceFromInterest,
                                                               const Eegeo::Resources::Interiors::InteriorId &interiorId,
                                                               int targetFloorIndex,
                                                               bool jumpIfFar)
            {
                const Eegeo::Space::EcefTangentBasis& cameraInterestBasis = m_cameraController.GetInterestBasis();
                
                float bearingRadians = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(cameraInterestBasis.GetPointEcef(),
                                                                                               cameraInterestBasis.GetForward());
                StartTransitionTo(newInterestPoint, distanceFromInterest, bearingRadians, interiorId, targetFloorIndex, jumpIfFar);
            }
            
            void CameraTransitionController::StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                                               float distanceFromInterest,
                                                               float newHeadingRadians,
                                                               const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                               int targetFloorIndex,
                                                               bool jumpIfFar)
            {
                if(IsTransitioning())
                {
                    StopCurrentTransition();
                }
                
                m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsModeOff);
                
                if(m_appModeModel.GetAppMode() == ExampleApp::AppModes::SdkModel::InteriorMode)
                {
                    if(m_interiorSelectionModel.GetSelectedInteriorId() == interiorId)
                    {
                        Eegeo_ASSERT(interiorId != Eegeo::Resources::Interiors::InteriorId::NullId(), "Invalid state. Have selected null Interior while in Interior mode");
                        EnqueueTransitionToInteriorStage(newInterestPoint, distanceFromInterest, interiorId, targetFloorIndex);
                        StartQueuedTransition();
                        return;
                    }
                    else
                    {
                        EnqueueExitInteriorStage();
                    }
                }
                
                EnqueueTransitionToPointStage(newInterestPoint, distanceFromInterest, newHeadingRadians, jumpIfFar);
                
                if(interiorId != m_interiorSelectionModel.GetSelectedInteriorId() && interiorId != Eegeo::Resources::Interiors::InteriorId::NullId())
                {
                    EnqueueTransitionToInteriorStage(newInterestPoint, distanceFromInterest, interiorId, targetFloorIndex);
                }
                
                StartQueuedTransition();
            }
            
            void CameraTransitionController::StartQueuedTransition()
            {
                Eegeo_ASSERT(!m_isTransitioning, "Cannot start transition as still running previous one");
                Eegeo_ASSERT(m_transitionStages.size() > 0, "Cannot start transition as no stages set");
                
                m_isTransitioning = true;
                m_transitionStages.front()->Start();
                
                m_messageBus.Publish(CameraTransitionChangedMessage(true));
            }
            
            void CameraTransitionController::StopCurrentTransition()
            {
                m_isTransitioning = false;
                size_t stageCount = m_transitionStages.size();
                for(size_t i = 0; i < stageCount; ++i)
                {
                    ICameraTransitionStage* pStage = m_transitionStages.front();
                    m_transitionStages.pop();
                    Eegeo_DELETE pStage;
                }
                
                m_messageBus.Publish(CameraTransitionChangedMessage(false));
            }

            void CameraTransitionController::Update(float dt)
            {
                if(!IsTransitioning())
                {
                    return;
                }

                ICameraTransitionStage* pCurrentStage = m_transitionStages.front();
                pCurrentStage->Update(dt);
                if(pCurrentStage->StageIsComplete())
                {
                    pCurrentStage->End();
                    Eegeo_DELETE pCurrentStage;
                    m_transitionStages.pop();
                    
                    if(m_transitionStages.size() > 0)
                    {
                        pCurrentStage = m_transitionStages.front();
                        pCurrentStage->Start();
                    }
                    else
                    {
                        StopCurrentTransition();
                    }
                }
                else if(pCurrentStage->StageHasFailed())
                {
                    StopCurrentTransition();
                }
            }
            
            void CameraTransitionController::EnqueueExitInteriorStage()
            {
                ICameraTransitionStage* pStage = Eegeo_NEW(ExitCurrentInteriorStage)(m_interiorsExplorerModel, m_appModeModel);
                m_transitionStages.push(pStage);
            }
            
            void CameraTransitionController::EnqueueTransitionToPointStage(const Eegeo::dv3& newInterestPoint,
                                                                           float distanceFromInterest,
                                                                           float newHeadingRadians,
                                                                           bool jumpIfFar)
            {
                ICameraTransitionStage* pStage = Eegeo_NEW(TransitionToWorldPointStage)(m_cameraController,
                                                                                        m_terrainHeightProvider,
                                                                                        newInterestPoint,
                                                                                        distanceFromInterest,
                                                                                        newHeadingRadians,
                                                                                        jumpIfFar);
                m_transitionStages.push(pStage);
            }
            
            void CameraTransitionController::EnqueueTransitionToInteriorStage(const Eegeo::dv3& newInterestPoint,
                                                                              float newDistanceToInterest,
                                                                              const Eegeo::Resources::Interiors::InteriorId &interiorId,
                                                                              int targetFloorIndex)
            {
                ICameraTransitionStage* pStage = Eegeo_NEW(TransitionToInteriorStage)(m_interiorController,
                                                                                      m_interiorSelectionModel,
                                                                                      m_interiorsCameraController,
                                                                                      newInterestPoint,
                                                                                      newDistanceToInterest,
                                                                                      interiorId,
                                                                                      targetFloorIndex);
                m_transitionStages.push(pStage);
            }
        }
    }
}
