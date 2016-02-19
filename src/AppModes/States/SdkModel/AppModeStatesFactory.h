// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IAppModeStatesFactory.h"
#include "IStateMachineState.h"
#include "Interiors.h"
#include "Streaming.h"
#include "InteriorsExplorer.h"
#include "AppCamera.h"
#include "AppModes.h"
#include "Tours.h"
#include "EegeoUI.h"
#include "MyPinCreation.h"

#include "VisualMap.h"

#include <vector>

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                class AppModeStatesFactory : public AppModes::SdkModel::IAppModeStatesFactory
                {
                private:
                    AppCamera::SdkModel::IAppCameraController& m_appCameraController;
                    Eegeo::Resources::Interiors::IInteriorController& m_interiorController;
                    AppCamera::SdkModel::AppGlobeCameraWrapper& m_worldCameraController;
                    AppCamera::SdkModel::AppInteriorCameraWrapper& m_interiorCameraController;
                    Tours::SdkModel::Camera::IToursCameraController& m_toursCameraController;
                    Eegeo::Streaming::CameraFrustumStreamingVolume& m_cameraFrustumStreamingVolume;
                    InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdate;
                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                    InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& m_interiorExplorerUserInteractionModel;
                    Tours::SdkModel::ITourService& m_tourService;
                    Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                    Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                    Eegeo::UI::NativeUIFactories& m_nativeUIFactories;
                    MyPinCreation::SdkModel::IMyPinCreationModel& m_myPinCreationModel;
                    VisualMap::SdkModel::IVisualMapService& m_visualMapService;

                    
                public:
                    
                    AppModeStatesFactory(AppCamera::SdkModel::IAppCameraController& appCameraController,
                                         Eegeo::Resources::Interiors::IInteriorController& interiorController,
                                         AppCamera::SdkModel::AppGlobeCameraWrapper& worldCameraController,
                                         AppCamera::SdkModel::AppInteriorCameraWrapper& interiorCameraController,
                                         Tours::SdkModel::Camera::IToursCameraController& toursCameraController,
                                         Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                         InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                         InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                         InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& interiorExplorerUserInteractionModel,
                                         AppModes::SdkModel::IAppModeModel& appModeModel,
                                         Tours::SdkModel::ITourService& tourService,
                                         Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                         Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                         Eegeo::UI::NativeUIFactories& nativeUIFactories,
                                         MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel,
                                         VisualMap::SdkModel::IVisualMapService& visualMapService);
                    
                    ~AppModeStatesFactory()
                    {
                        
                    }
                    
                    const std::vector<Helpers::IStateMachineState*> CreateStateMachineStates();
                };
            }
        }
    }
}
