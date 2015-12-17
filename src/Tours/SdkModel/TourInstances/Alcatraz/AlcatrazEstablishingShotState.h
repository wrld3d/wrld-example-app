// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "ITourStateMachineState.h"
#include "Tours.h"
#include "TourStateModel.h"
#include "SplineCameraMode.h"
#include "WorldPins.h"
#include "IWeatherController.h"
#include "CatmullRomSpline.h"
#include "Audio.h"
#include "PlaceNamesViewFilter.h"
#include "SceneModel.h"
#include "IAsyncTextureRequestor.h"
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
                    class AlcatrazEstablishingShotState : public States::ITourStateMachineState, private Eegeo::NonCopyable
                    {
                        TourStateModel m_stateModel;
                        Eegeo::Geometry::CatmullRomSpline m_positionSpline;
                        Eegeo::Geometry::CatmullRomSpline m_targetSpline;
                        Camera::SplineCameraMode* m_pSplineCameraMode;
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        bool m_cameraTransitionComplete;
                        VisualMap::SdkModel::IVisualMapService& m_visualMapService;
                        Eegeo::Resources::PlaceNames::PlaceNamesViewFilter& m_placeNamesViewFilter;
                        std::string m_timeOnStateEntry;
                        Audio::IAudioPlaybackInstanceFactory& m_audioPlaybackInstanceFactory;
                        Audio::IAudioPlaybackInstance* m_pAudioPlaybackInstance;
                        Eegeo::Rendering::SceneModels::SceneModelLoader& m_sceneModelLoader;
                        Eegeo::Rendering::Filters::SceneModelRenderableFilter& m_sceneModelRenderableFilter;
                        Eegeo::Rendering::SceneModels::SceneModel* m_pBoatModel;
                                                
                    public:
                        AlcatrazEstablishingShotState(const TourStateModel& stateModel,
                                                      Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                      VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                      Eegeo::Resources::PlaceNames::PlaceNamesViewFilter& placeNamesViewFilter,
                                                      Audio::IAudioPlaybackInstanceFactory& audioPlaybackInstanceFactory,
                                                      Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                                      Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter);
                        
                        ~AlcatrazEstablishingShotState();
                        
                        void Enter();
                        
                        void Update(float dt);
                        
                        void Exit();
                    };
                }
            }
        }
    }
}
