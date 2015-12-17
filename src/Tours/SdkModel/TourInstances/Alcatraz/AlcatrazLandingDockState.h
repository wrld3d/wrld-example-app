// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ITourStateMachineState.h"
#include "Tours.h"
#include "TourStateModel.h"
#include "SplineCameraMode.h"
#include "CatmullRomSpline.h"
#include "Audio.h"
#include "IAsyncTextureRequestor.h"
#include "SceneModel.h"
#include "IFileIO.h"
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
                    class AlcatrazLandingDockState : public States::ITourStateMachineState, private Eegeo::NonCopyable
                    {
                        TourStateModel m_stateModel;
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        Eegeo::Geometry::CatmullRomSpline m_positionSpline;
                        Eegeo::Geometry::CatmullRomSpline m_targetSpline;
                        Camera::SplineCameraMode* m_pSplineCameraMode;
                        Eegeo::Geometry::CatmullRomSpline m_positionCraneSpline;
                        Eegeo::Geometry::CatmullRomSpline m_targetCraneSpline;
                        Camera::SplineCameraMode* m_pCraneCameraMode;
                        bool m_cameraTransitionComplete;
                        Audio::IAudioPlaybackInstanceFactory& m_audioPlaybackInstanceFactory;
                        Audio::IAudioPlaybackInstance* m_pAudioPlaybackInstance;
                        VisualMap::SdkModel::IVisualMapService& m_visualMapService;

                        Eegeo::Rendering::SceneModels::SceneModelLoader& m_sceneModelLoader;
                        Eegeo::Rendering::Filters::SceneModelRenderableFilter& m_sceneModelRenderableFilter;
                        Eegeo::Rendering::SceneModels::SceneModel* m_pBoatModel;
                        
                    public:
                        AlcatrazLandingDockState(const TourStateModel& stateModel,
                                                 Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                 VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                 Audio::IAudioPlaybackInstanceFactory& audioPlaybackInstanceFactory,
                                                 Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                                 Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter);
                        
                        ~AlcatrazLandingDockState();
                        
                        void Enter();
                        
                        void Update(float dt);
                        
                        void Exit();
                    };
                }
            }
        }
    }
}
