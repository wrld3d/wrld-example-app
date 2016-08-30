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
#include "InteriorsNavigation.h"
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

                CameraTransitionController(const std::shared_ptr<Eegeo::Camera::GlobeCamera::GpsGlobeCameraController>& cameraController,
                                           const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController>& interiorsCameraController,
                                           const std::shared_ptr<Eegeo::Location::NavigationService>& navigationService,
                                           const std::shared_ptr<ExampleApp::InteriorsNavigation::SdkModel::IInteriorsNavigationService>& interiorsNavigationService,
                                           const std::shared_ptr<Eegeo::Resources::Terrain::Heights::TerrainHeightProvider>& terrainHeightProvider,
                                           const std::shared_ptr<ExampleApp::AppModes::SdkModel::IAppModeModel>& appModeModel,
                                           const std::shared_ptr<ExampleApp::AppCamera::SdkModel::IAppCameraController>& appCameraController,
                                           const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel>& interiorSelectionModel,
                                           const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel,
                                           const std::shared_ptr<Eegeo::Resources::Interiors::InteriorTransitionModel>& interiorTransitionModel,
                                           const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorsExplorerModel>& interiorsExplorerModel,
                                           const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

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
                                       bool jumpIfFar=true);
                
                void StopCurrentTransition();
                void Update(float dt);

                const bool IsTransitioning() const
                {
                    return m_isTransitioning;
                }
                
                void InsertTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveTransitioningChangedCallback(Eegeo::Helpers::ICallback0& callback);

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
                
                void EnqueueTransitionToInteriorPointStage(const Eegeo::dv3& newInterestPoint,
                                                           float newDistanceFromInterest,
                                                           float newHeadingRadians,
                                                           const Eegeo::Resources::Interiors::InteriorId &interiorId,
                                                           int targetFloorIndex,
                                                           bool jumpIfFar=true);
                
                void StartQueuedTransition();
                
                const std::shared_ptr<Eegeo::Camera::GlobeCamera::GpsGlobeCameraController> m_cameraController;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController> m_interiorsCameraController;
                const std::shared_ptr<Eegeo::Location::NavigationService> m_navigationService;
                const std::shared_ptr<ExampleApp::InteriorsNavigation::SdkModel::IInteriorsNavigationService> m_interiorsNavigationService;
                const std::shared_ptr<Eegeo::Resources::Terrain::Heights::TerrainHeightProvider> m_terrainHeightProvider;
                const std::shared_ptr<ExampleApp::AppModes::SdkModel::IAppModeModel> m_appModeModel;
                const std::shared_ptr<ExampleApp::AppCamera::SdkModel::IAppCameraController> m_appCameraController;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel> m_interiorSelectionModel;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel> m_interiorInteractionModel;
                const std::shared_ptr<const Eegeo::Resources::Interiors::InteriorTransitionModel> m_interiorTransitionModel;
                const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorsExplorerModel> m_interiorsExplorerModel;
               
                Eegeo::Resources::Interiors::InteriorId m_defaultInteriorId;
                bool m_isTransitioning;
                
                Eegeo::Helpers::CallbackCollection0 m_transitioningChangedCallbacks;
            };
        }
    }
}
