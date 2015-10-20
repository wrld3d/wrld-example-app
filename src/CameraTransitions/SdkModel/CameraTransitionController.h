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
                                           ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& interiorsCameraController,
                                           Eegeo::Location::NavigationService& navigationService,
                                           Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                           ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                           Eegeo::Resources::Interiors::InteriorController& interiorController,
                                           InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                           ExampleAppMessaging::TMessageBus& messageBus);

                void StartTransitionTo(const Eegeo::dv3& newInterestPoint,
                                       float distanceFromInterest,
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
                                       bool jumpIfFar=true);
                
                void StopCurrentTransition();
                void Update(float dt);

                const bool IsTransitioning() const
                {
                    return m_isTransitioning;
                }

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
                                                      int targetFloorIndex);
                void StartQueuedTransition();
                
                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_cameraController;
                ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& m_interiorsCameraController;
                Eegeo::Location::NavigationService& m_navigationService;
                Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;
                ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
               
                Eegeo::Resources::Interiors::InteriorId m_defaultInteriorId;
                bool m_isTransitioning;
                
            };
        }
    }
}
