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
#include "InteriorsCameraController.h"
#include "IAppModeModel.h"
#include "InteriorSelectionModel.h"
#include "TransitionToWorldPointStage.h"
#include "TransitionToInteriorPointStage.h"
#include "ExitCurrentInteriorStage.h"
#include "TransitionToInteriorStage.h"
#include "IAppCameraController.h"
#include "InteriorsModelRepository.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            CameraTransitionController::CameraTransitionController(Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController,
                                                                   Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                                                   Eegeo::Location::NavigationService& navigationService,
                                                                   Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                                                   ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                   ExampleApp::AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                                   Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                   Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                   const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                                                   InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                                   Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                                   ExampleApp::ExampleAppMessaging::TMessageBus& messageBus)
            : m_cameraController(cameraController)
            , m_interiorsCameraController(interiorsCameraController)
            , m_navigationService(navigationService)
            , m_terrainHeightProvider(terrainHeightProvider)
            , m_appModeModel(appModeModel)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_interiorTransitionModel(interiorTransitionModel)
            , m_appCameraController(appCameraController)
            , m_interiorsExplorerModel(interiorsExplorerModel)
            , m_interiorsModelRepository(interiorsModelRepository)
            , m_isTransitioning(false)
            , m_defaultInteriorId(Eegeo::Resources::Interiors::InteriorId::NullId())
            {

            }
            
            void CameraTransitionController::StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                                               float distanceFromInterest,
                                                               bool jumpIfFar)
            {
                float bearingRadians = Eegeo::Math::Deg2Rad(m_appCameraController.GetHeadingDegrees());

                StartTransitionTo(newInterestPoint, distanceFromInterest, bearingRadians, m_defaultInteriorId, 0, jumpIfFar);
            }
            
            void CameraTransitionController::StartTransitionTo(float distanceFromInterest,
                                                               const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                               int targetFloorIndex,
                                                               bool jumpIfFar)
            {
                float bearingRadians = Eegeo::Math::Deg2Rad(m_appCameraController.GetHeadingDegrees());
                StartTransitionTo(m_interiorsCameraController.GetInterestLocation(),distanceFromInterest,bearingRadians,interiorId,targetFloorIndex,jumpIfFar);
                
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
                float bearingRadians = Eegeo::Math::Deg2Rad(m_appCameraController.GetHeadingDegrees());
                
                StartTransitionTo(newInterestPoint, distanceFromInterest, bearingRadians, interiorId, targetFloorIndex, jumpIfFar);
            }

            void CameraTransitionController::StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                                               float distanceFromInterest,
                                                               float newHeadingRadians,
                                                               const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                               int targetFloorIndex,
                                                               bool jumpIfFar,
                                                               bool setGpsModeOff,
                                                               bool setInteriorHeading,
                                                               bool setDistanceToInterest)
            {
                if(IsTransitioning())
                {
                    StopCurrentTransition();
                }
                
                if(setGpsModeOff)
                {
                    m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsModeOff);
                }
                
                if(m_appModeModel.GetAppMode() == ExampleApp::AppModes::SdkModel::InteriorMode)
                {
                    const double exitInteriorDistanceSquared = 100*100;
                    double interestDifferenceSquared = (m_interiorsCameraController.GetInterestLocation() - newInterestPoint).LengthSq();
                    if(m_interiorSelectionModel.GetSelectedInteriorId() == interiorId)
                    {
                        Eegeo_ASSERT(interiorId != Eegeo::Resources::Interiors::InteriorId::NullId(), "Invalid state. Have selected null Interior while in Interior mode");
                        EnqueueTransitionToInteriorStage(newInterestPoint, distanceFromInterest, interiorId, targetFloorIndex, newHeadingRadians, setInteriorHeading, setDistanceToInterest);
                        StartQueuedTransition();
                        return;
                    }
                    else if(interiorId != Eegeo::Resources::Interiors::InteriorId::NullId() && interestDifferenceSquared < exitInteriorDistanceSquared && m_interiorsModelRepository.HasInterior(interiorId.Value()))
                    {
                        EnqueueTransitionToInteriorPointStage(newInterestPoint, distanceFromInterest, newHeadingRadians, interiorId, targetFloorIndex, jumpIfFar);
                        StartQueuedTransition();
                        return;
                    }
                    else
                    {
                        EnqueueExitInteriorStage();
                    }
                }
                
                const bool transitioningToNewInterior = interiorId != m_interiorSelectionModel.GetSelectedInteriorId() && interiorId != Eegeo::Resources::Interiors::InteriorId::NullId();
                
                if(!transitioningToNewInterior)
                {
                    EnqueueTransitionToPointStage(newInterestPoint, distanceFromInterest, newHeadingRadians, jumpIfFar);
                }
                else
                {
                    EnqueueTransitionToInteriorStage(newInterestPoint, distanceFromInterest, interiorId, targetFloorIndex, newHeadingRadians, setInteriorHeading);
                }
                
                StartQueuedTransition();
            }
            
            void CameraTransitionController::StartQueuedTransition()
            {
                Eegeo_ASSERT(!m_isTransitioning, "Cannot start transition as still running previous one");
                Eegeo_ASSERT(m_transitionStages.size() > 0, "Cannot start transition as no stages set");
                
                m_isTransitioning = true;
                m_transitionStages.front()->Start();
                
                m_transitioningChangedCallbacks.ExecuteCallbacks();
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
                m_transitioningChangedCallbacks.ExecuteCallbacks();
            }

            void CameraTransitionController::Update(float dt)
            {
                if(!IsTransitioning())
                {
                    return;
                }

                ICameraTransitionStage* pCurrentStage = m_transitionStages.front();
                pCurrentStage->Update(dt);
                if(pCurrentStage->StageIsComplete() && !m_appCameraController.IsTransitionInFlight())
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
                        m_transitionCompletedCallbacks.ExecuteCallbacks();
                    }
                }
                else if(pCurrentStage->StageHasFailed())
                {
                    StopCurrentTransition();
                }
            }
            
            void CameraTransitionController::InsertTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_transitioningChangedCallbacks.AddCallback(callback);
            }
            void CameraTransitionController::RemoveTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_transitioningChangedCallbacks.RemoveCallback(callback);
            }

            void CameraTransitionController::InsertTransitionCompletedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_transitionCompletedCallbacks.AddCallback(callback);
            }
            void CameraTransitionController::RemoveTransitionCompletedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_transitionCompletedCallbacks.RemoveCallback(callback);
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
                                                                              int targetFloorIndex,
                                                                              float newHeadingRadians,
                                                                              bool setInteriorHeading,
                                                                              bool setDisntaceToInterest)
            {
                ICameraTransitionStage* pStage = Eegeo_NEW(TransitionToInteriorStage)(m_interiorInteractionModel,
                                                                                      m_interiorSelectionModel,
                                                                                      m_interiorTransitionModel,
                                                                                      m_interiorsCameraController,
                                                                                      newInterestPoint,
                                                                                      newDistanceToInterest,
                                                                                      interiorId,
                                                                                      targetFloorIndex,
                                                                                      setInteriorHeading,
                                                                                      newHeadingRadians,
                                                                                      setDisntaceToInterest);
                m_transitionStages.push(pStage);
            }
            
            void CameraTransitionController::EnqueueTransitionToInteriorPointStage(const Eegeo::dv3& newInterestPoint,
                                                                                   float newDistanceFromInterest,
                                                                                   float newHeadingRadians,
                                                                                   const Eegeo::Resources::Interiors::InteriorId &interiorId,
                                                                                   int targetFloorIndex,
                                                                                   bool jumpIfFar)
            {
                ICameraTransitionStage* pStage = Eegeo_NEW(TransitionToInteriorPointStage)(
                                                                                           m_interiorInteractionModel,
                                                                                           m_interiorSelectionModel,
                                                                                           m_interiorTransitionModel,
                                                                                           m_interiorsExplorerModel,
                                                                                           m_interiorsCameraController,
                                                                                           newInterestPoint,
                                                                                           newDistanceFromInterest,
                                                                                           interiorId,
                                                                                           targetFloorIndex,
                                                                                           jumpIfFar);
                m_transitionStages.push(pStage);

            }
        }
    }
}
