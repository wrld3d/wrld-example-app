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
                    class AlcatrazCellHouseDetailState : public States::ITourStateMachineState, private Eegeo::NonCopyable
                    {
                        TourStateModel m_stateModel;
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        Camera::MapCameraMode m_cameraMode;
                        bool m_cameraTransitionComplete;
                        Audio::IAudioPlaybackInstanceFactory& m_audioPlaybackInstanceFactory;
                        Audio::IAudioPlaybackInstance* m_pAudioPlaybackInstance;
                        VisualMap::SdkModel::IVisualMapService& m_visualMapService;
                        ExampleAppMessaging::TMessageBus& m_messageBus;
                        
                        bool m_heroCardInYourFace;
                    public:
                        AlcatrazCellHouseDetailState(const TourStateModel& stateModel,
                                                     Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                     Audio::IAudioPlaybackInstanceFactory& audioPlaybackInstanceFactory,
                                                     VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                     const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                     Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                                     Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory& cameraControllerFactory);
                        
                        ~AlcatrazCellHouseDetailState();
                        
                        void Enter();
                        
                        void Update(float dt);
                        
                        void Exit();
                    };
                }
            }
        }
    }
}
