// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "Types.h"
#include "ITourStateMachineState.h"
#include "Tours.h"
#include "TourStateModel.h"
#include "MapCameraMode.h"
#include "Audio.h"
#include "WorldPins.h"
#include "BidirectionalBus.h"
#include "Rendering.h"
#include "GlobeCamera.h"
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
                    class AlcatrazRecreationYardState : public States::ITourStateMachineState, private Eegeo::NonCopyable
                    {
                        TourStateModel m_stateModel;
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        Camera::MapCameraMode m_cameraMode;
                        bool m_cameraTransitionComplete;
                        Audio::IAudioPlaybackInstanceFactory& m_audioPlaybackInstanceFactory;
                        Audio::IAudioPlaybackInstance* m_pAudioPlaybackInstance;
                        VisualMap::SdkModel::IVisualMapService& m_visualMapService;
                        WorldPins::SdkModel::IWorldPinsService& m_toursWorldPinsService;
                        ExampleAppMessaging::TMessageBus& m_messageBus;
                        std::vector<WorldPins::SdkModel::WorldPinItemModel*> m_alcatrazSharedTourPins;
                        
                    public:
                        AlcatrazRecreationYardState(const TourStateModel& stateModel,
                                                    Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                    VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                    Audio::IAudioPlaybackInstanceFactory& audioPlaybackInstanceFactory,
                                                    WorldPins::SdkModel::IWorldPinsService& toursWorldPinsService,
                                                    ExampleAppMessaging::TMessageBus& messageBus,
                                                    const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                                    Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory& cameraControllerFactory);
                        
                        ~AlcatrazRecreationYardState();
                        
                        void Enter();
                        
                        void Update(float dt);
                        
                        void Exit();
                    };
                }
            }
        }
    }
}
