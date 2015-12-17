// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "Types.h"
#include "ITourStateMachineState.h"
#include "Tours.h"
#include "TourStateModel.h"
#include "OrbitCameraMode.h"
#include "Audio.h"
#include "IAsyncTextureRequestor.h"
#include "SceneModel.h"
#include "IFileIO.h"
#include "Rendering.h"
#include "MapCameraMode.h"
#include "WorldPins.h"
#include "BidirectionalBus.h"
#include "GlobeCamera.h"
#include "Rendering.h"
#include "VisualMap.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace Alcatraz
                {
                    class AlcatrazCellHouseIntroState : public States::ITourStateMachineState, private Eegeo::NonCopyable
                    {
                        TourStateModel m_stateModel;
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        Camera::MapCameraMode m_cameraMode;
                        bool m_cameraTransitionComplete;
                        Audio::IAudioPlaybackInstanceFactory& m_audioPlaybackInstanceFactory;
                        Audio::IAudioPlaybackInstance* m_pAudioPlaybackInstance;
                        Eegeo::Rendering::SceneModels::SceneModelLoader& m_sceneModelLoader;
                        Eegeo::Rendering::Filters::SceneModelRenderableFilter& m_sceneModelRenderableFilter;
                        Eegeo::Rendering::SceneModels::SceneModel* m_pBoatModel;
                        VisualMap::SdkModel::IVisualMapService& m_visualMapService;
                        float m_timeInState;
                        ExampleAppMessaging::TMessageBus& m_messageBus;
                        WorldPins::SdkModel::IWorldPinsService& m_toursWorldPinsService;
                        std::vector<WorldPins::SdkModel::WorldPinItemModel*> m_alcatrazSharedTourPins;
                    public:
                        AlcatrazCellHouseIntroState(const TourStateModel& stateModel,
                                                    Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                    Audio::IAudioPlaybackInstanceFactory& audioPlaybackInstanceFactory,
                                                    Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                                    Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter,
                                                    VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                    WorldPins::SdkModel::IWorldPinsService& toursWorldPinsService,
                                                    ExampleAppMessaging::TMessageBus& messageBus,
                                                    const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                                    Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory& cameraControllerFactory);
                        
                        ~AlcatrazCellHouseIntroState();
                        
                        void Enter();
                        
                        void Update(float dt);
                        
                        void Exit();
                    };
                }
            }
        }
    }
}
