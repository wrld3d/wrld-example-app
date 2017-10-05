// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICameraTransitionController.h"
#include "GlobeCamera.h"
#include "Location.h"
#include "VectorMath.h"
#include "Terrain.h"
#include "Interiors.h"
#include "CameraTransitions.h"
#include "AppModes.h"
#include "InteriorsExplorer.h"
#include "InteriorId.h"
#include <queue>
#include "AppCamera.h"
#include "CallbackCollection.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            class CameraTransitionController : public ICameraTransitionController
            {
            public:

                CameraTransitionController(Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController,
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
                                           ExampleAppMessaging::TMessageBus& messageBus);

                void StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                       float distanceFromInterest,
                                       bool jumpIfFar=true);
                void StartTransitionTo(float distanceFromInterest,
                                       const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                       int targetFloorIndex,
                                       bool jumpIfFar=true);
                void StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                       float distanceFromInterest,
                                       float newHeadingRadians,
                                       bool jumpIfFar=true);
                
                void StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                       float distanceFromInterest,
                                       const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                       int targetFloorIndex,
                                       bool jumpIfFar=true);
                
                void StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                       float distanceFromInterest,
                                       float newHeadingRadians,
                                       const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                       int targetFloorIndex,
                                       bool jumpIfFar=true,
                                       bool setGpsModeOff=true,
                                       bool setInteriorHeading=false,
                                       bool setDistanceToInterest=true);
                
                void StopCurrentTransition();
                void Update(float dt);

                const bool IsTransitioning() const
                {
                    return m_isTransitioning;
                }
                
                void InsertTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertTransitionCompletedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveTransitionCompletedCallback(Eegeo::Helpers::ICallback0& callback);

            private:

                std::queue<ICameraTransitionStage*> m_transitionStages;
                
                void EnqueueExitInteriorStage();
                
                void EnqueueTransitionToPointStage(const Eegeo::dv3& newInterestPoint,
                                                   float distanceFromInterest,
                                                   float newHeadingRadians,
                                                   bool jumpIfFar=true);
                
                void EnqueueTransitionToInteriorStage(const Eegeo::dv3& newInterestPoint,
                                                      float newDistanceToInterest,
                                                      const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                      int targetFloorIndex,
                                                      float newHeadingRadians,
                                                      bool setInteriorHeading=false,
                                                      bool setDisntaceToInterest=true);
                
                void EnqueueTransitionToInteriorPointStage(const Eegeo::dv3& newInterestPoint,
                                                           float newDistanceFromInterest,
                                                           float newHeadingRadians,
                                                           const Eegeo::Resources::Interiors::InteriorId &interiorId,
                                                           int targetFloorIndex,
                                                           bool jumpIfFar=true);
                
                void StartQueuedTransition();
                
                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_cameraController;
                Eegeo::Resources::Interiors::InteriorsCameraController& m_interiorsCameraController;
                Eegeo::Location::NavigationService& m_navigationService;
                Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;
                ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
                ExampleApp::AppCamera::SdkModel::IAppCameraController& m_appCameraController;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                const Eegeo::Resources::Interiors::InteriorTransitionModel& m_interiorTransitionModel;
                InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                Eegeo::Resources::Interiors::InteriorsModelRepository& m_interiorsModelRepository;
               
                Eegeo::Resources::Interiors::InteriorId m_defaultInteriorId;
                bool m_isTransitioning;
                
                Eegeo::Helpers::CallbackCollection0 m_transitioningChangedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_transitionCompletedCallbacks;
            };
        }
    }
}
