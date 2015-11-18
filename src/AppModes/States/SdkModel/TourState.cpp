// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourState.h"
#include "IAppCameraController.h"
#include "TourService.h"
#include "IAppModeModel.h"
#include "InteriorSelectionModel.h"
#include "CameraHelpers.h"
#include "CameraState.h"
#include "RenderCamera.h"
#include "GlobeCameraController.h"
#include "GpsGlobeCameraController.h"
#include "InteriorsExplorerCameraController.h"
#include "MathFunc.h"
#include "IMapModeModel.h"
#include "MyPinCreationModel.h"
#include "MyPinCreationStage.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                TourState::TourState(AppCamera::SdkModel::IAppCameraController& cameraController,
                                     int tourCameraHandle,
                                     Tours::SdkModel::ITourService& tourService,
                                     Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                     AppModes::SdkModel::IAppModeModel& appModeModel,
                                     Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& worldCameraController,
                                     ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& interiorsCameraController,
                                     MapMode::SdkModel::IMapModeModel& mapModeModel,
                                     MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel)
                : m_cameraController(cameraController)
                , m_tourCameraHandle(tourCameraHandle)
                , m_tourService(tourService)
                , m_tourStartedCallback(this, &TourState::OnTourEnded)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_appModeModel(appModeModel)
                , m_worldCameraController(worldCameraController)
                , m_interiorsCameraController(interiorsCameraController)
                , m_mapModeModel(mapModeModel)
                , m_previousMapModeState(false)
                , m_myPinCreationModel(myPinCreationModel)
                {
                }
                
                TourState::~TourState()
                {
                }
                
                void TourState::Enter()
                {
                    m_cameraController.TransitionToCameraWithHandle(m_tourCameraHandle);
                    m_tourService.RegisterTourEndedCallback(m_tourStartedCallback);
                    
                    m_previousMapModeState = m_mapModeModel.IsInMapMode();
                    m_mapModeModel.SetInMapMode(false);
                    
                    m_myPinCreationModel.SetCreationStage(MyPinCreation::Inactive);
                }
                
                void TourState::Update(float dt)
                {
                }
                
                void TourState::Exit()
                {
                    m_tourService.UnregisterTourEndedCallback(m_tourStartedCallback);
                    
                    const float interestDistance = m_appModeModel.GetAppMode() == AppModes::SdkModel::WorldMode ? 500.0f : 150.0f;
                    
                    if(m_appModeModel.GetAppMode() == AppModes::SdkModel::WorldMode)
                    {
                        Eegeo::Space::LatLongAltitude latLong = Eegeo::Space::LatLongAltitude::FromECEF(m_cameraController.GetCameraState().InterestPointEcef());
                        
                        m_worldCameraController.SetView(latLong.GetLatitudeInDegrees(), latLong.GetLongitudeInDegrees(),
                                                        m_cameraController.GetHeadingDegrees(),
                                                        interestDistance);
                        m_worldCameraController.GetGlobeCameraController().ApplyTilt(0.0f);
                    }
                    else if(m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
                    {
                        m_interiorsCameraController.SetDistanceToInterest(interestDistance);
                        m_interiorsCameraController.SetHeading(m_cameraController.GetHeadingDegrees());
                        m_interiorsCameraController.SetInterestLocation(m_cameraController.GetCameraState().InterestPointEcef());
                    }
                    
                    m_mapModeModel.SetInMapMode(m_previousMapModeState);
                }

                
                void TourState::OnTourEnded()
                {
                    const ExampleApp::AppModes::SdkModel::AppMode mode = m_interiorSelectionModel.IsInteriorSelected() ?
                                ExampleApp::AppModes::SdkModel::InteriorMode : ExampleApp::AppModes::SdkModel::WorldMode;
                    
                    m_appModeModel.SetAppMode(mode);
                }
                
            }
        }
    }
}