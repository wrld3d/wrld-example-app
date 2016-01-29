// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldState.h"
#include "IAppCameraController.h"
#include "TourService.h"
#include "IAppModeModel.h"
#include "InteriorSelectionModel.h"
#include "CameraHelpers.h"
#include "IAppCameraController.h"
#include "CameraState.h"
#include "RenderCamera.h"
#include "InteriorsExplorerCameraController.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                WorldState::WorldState(AppCamera::SdkModel::IAppCameraController& cameraController,
                                       int worldCameraHandle,
                                       Tours::SdkModel::ITourService& tourService,
                                       Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                       AppModes::SdkModel::IAppModeModel& appModeModel,
                                       ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& interiorsCameraController)
                : m_cameraController(cameraController)
                , m_worldCameraHandle(worldCameraHandle)
                , m_tourService(tourService)
                , m_tourStartedCallback(this, &WorldState::OnTourStarted)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_interiorSelectionModelChangedCallback(this, &WorldState::OnInteriorSelectionModelChanged)
                , m_appModeModel(appModeModel)
                , m_interiorsCameraController(interiorsCameraController)
                {
                }
                
                WorldState::~WorldState()
                {
                }
                
                void WorldState::Enter(int previousState)
                {
                    m_cameraController.TransitionToCameraWithHandle(m_worldCameraHandle);
                    m_tourService.RegisterTourStartedCallback(m_tourStartedCallback);
                    m_interiorSelectionModel.RegisterSelectionChangedCallback(m_interiorSelectionModelChangedCallback);
                }
                
                void WorldState::Update(float dt)
                {
                    
                }
                
                void WorldState::Exit(int nextState)
                {
                    m_tourService.UnregisterTourStartedCallback(m_tourStartedCallback);
                    m_interiorSelectionModel.UnregisterSelectionChangedCallback(m_interiorSelectionModelChangedCallback);
                    
                    if(nextState == AppModes::SdkModel::InteriorMode)
                    {
                        m_interiorsCameraController.SetHeading(m_cameraController.GetHeadingDegrees());
                        //m_interiorsCameraController.SetTilt(0.0f);
                    }
                }
                
                void WorldState::OnTourStarted()
                {
                    m_appModeModel.SetAppMode(ExampleApp::AppModes::SdkModel::TourMode);
                }
                
                void WorldState::OnInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId)
                {
                    if(m_interiorSelectionModel.IsInteriorSelected())
                    {
                        m_appModeModel.SetAppMode(ExampleApp::AppModes::SdkModel::InteriorMode);
                    }
                }
            }
        }
    }
}