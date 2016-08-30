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
#include "Types.h"

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
                class AppModeStatesFactory : public AppModes::SdkModel::IAppModeStatesFactory, private Eegeo::NonCopyable
                {
                private:
                    const std::shared_ptr<AppCamera::SdkModel::IAppCameraController> m_appCameraController;
                    const std::shared_ptr<AppCamera::SdkModel::AppGlobeCameraWrapper> m_worldCameraController;
                    const std::shared_ptr<AppCamera::SdkModel::AppInteriorCameraWrapper> m_interiorCameraController;
                    const std::shared_ptr<Tours::SdkModel::Camera::IToursCameraController> m_toursCameraController;
                    const std::shared_ptr<Eegeo::Streaming::CameraFrustumStreamingVolume> m_cameraFrustumStreamingVolume;
                    const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorVisibilityUpdater> m_interiorVisibilityUpdate;
                    const std::shared_ptr<AppModes::SdkModel::IAppModeModel> m_appModeModel;
                    const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorsExplorerModel> m_interiorsExplorerModel;
                    const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel> m_interiorExplorerUserInteractionModel;
                    const std::shared_ptr<Tours::SdkModel::ITourService> m_tourService;
                    const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel> m_interiorSelectionModel;
                    const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel> m_interiorInteractionModel;
                    const std::shared_ptr<Eegeo::UI::NativeUIFactories> m_nativeUIFactories;
                    const std::shared_ptr<MyPinCreation::SdkModel::IMyPinCreationModel> m_myPinCreationModel;
                    const std::shared_ptr<VisualMap::SdkModel::IVisualMapService> m_visualMapService;

                    
                public:
                    
                    AppModeStatesFactory(const std::shared_ptr<AppCamera::SdkModel::IAppCameraController>& appCameraController,
                                         const std::shared_ptr<AppCamera::SdkModel::AppGlobeCameraWrapper>& worldCameraController,
                                         const std::shared_ptr<AppCamera::SdkModel::AppInteriorCameraWrapper>& interiorCameraController,
                                         const std::shared_ptr<Tours::SdkModel::Camera::IToursCameraController>& toursCameraController,
                                         const std::shared_ptr<Eegeo::Streaming::CameraFrustumStreamingVolume>& cameraFrustumStreamingVolume,
                                         const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorVisibilityUpdater>& interiorVisibilityUpdater,
                                         const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorsExplorerModel>& interiorsExplorerModel,
                                         const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel>& interiorExplorerUserInteractionModel,
                                         const std::shared_ptr<AppModes::SdkModel::IAppModeModel>& appModeModel,
                                         const std::shared_ptr<Tours::SdkModel::ITourService>& tourService,
                                         const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel>& interiorSelectionModel,
                                         const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel,
                                         const std::shared_ptr<Eegeo::UI::NativeUIFactories>& nativeUIFactories,
                                         const std::shared_ptr<MyPinCreation::SdkModel::IMyPinCreationModel>& myPinCreationModel,
                                         const std::shared_ptr<VisualMap::SdkModel::IVisualMapService>& visualMapService);
                    
                    ~AppModeStatesFactory()
                    {
                        
                    }
                    
                    const std::vector<Helpers::IStateMachineState*> CreateStateMachineStates();
                };
            }
        }
    }
}
