// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AlcatrazEstablishingShotState.h"
#include "Logger.h"
#include "IToursCameraTransitionController.h"
#include "LatLongAltitude.h"
#include "IAudioPlaybackInstanceFactory.h"
#include "IAudioPlaybackInstance.h"
#include "SceneModelLoader.h"
#include "SceneModel.h"
#include "SceneModelRenderableFilter.h"
#include "AlcatrazTourHelpers.h"
#include "IVisualMapService.h"
#include "VisualMapState.h"

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
                    AlcatrazEstablishingShotState::AlcatrazEstablishingShotState(const TourStateModel& stateModel,
                                                                                 Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                                                 VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                                                 Eegeo::Resources::PlaceNames::PlaceNamesViewFilter& placeNamesViewFilter,
                                                                                 Audio::IAudioPlaybackInstanceFactory& audioPlaybackInstanceFactory,
                                                                                 Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                                                                 Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter)
                    : m_stateModel(stateModel)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_visualMapService(visualMapService)
                    , m_placeNamesViewFilter(placeNamesViewFilter)
                    , m_audioPlaybackInstanceFactory(audioPlaybackInstanceFactory)
                    , m_pAudioPlaybackInstance(m_audioPlaybackInstanceFactory.CreateAudio("Tours/States/Alcatraz/card1.mp3"))
                    , m_sceneModelLoader(sceneModelLoader)
                    , m_sceneModelRenderableFilter(sceneModelRenderableFilter)
                    , m_pBoatModel(NULL)
                    {
                        m_positionSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.7933, -122.389, 1333.99).ToECEF());
                        m_positionSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.8037, -122.401, 659.37).ToECEF());
                        m_positionSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.8263, -122.413, 601.633).ToECEF());
                        m_targetSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.8002, -122.401, 4.83844).ToECEF());
                        m_targetSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.809, -122.405, -5.00206).ToECEF());
                        m_targetSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.8266, -122.42, -5.01118).ToECEF());
                        
                        const float startFieldOfViewDegrees(40.f);
                        const float endFieldOfViewDegrees(40.f);
                        const float playbackRateMultiplier(0.05f);
                        
                        m_pSplineCameraMode = Eegeo_NEW(Tours::SdkModel::Camera::SplineCameraMode)(&m_positionSpline,
                                                                                                   &m_targetSpline,
                                                                                                   startFieldOfViewDegrees,
                                                                                                   endFieldOfViewDegrees,
                                                                                                   playbackRateMultiplier);
                        
                        m_pBoatModel = m_sceneModelLoader.LoadPOD("Tours/States/Alcatraz/Boats/Ferry.POD");
                    }
                
                    AlcatrazEstablishingShotState::~AlcatrazEstablishingShotState()
                    {
                        Eegeo_DELETE m_pAudioPlaybackInstance;
                        Eegeo_DELETE m_pBoatModel;
                    }
                    
                    void AlcatrazEstablishingShotState::Enter()
                    {
                        EXAMPLE_LOG("State %s: Enter.\n", m_stateModel.Headline().c_str());

                        m_visualMapService.SetVisualMapThemeState("DawnFoggy");
                        m_cameraTransitionComplete = false;
                        
                        m_pSplineCameraMode->Reset();
                        m_toursCameraTransitionController.TransitionTo(*m_pSplineCameraMode, false);
                        
                        m_pAudioPlaybackInstance->Reset();
                        m_pAudioPlaybackInstance->Play();
                        
                        m_placeNamesViewFilter.SetEnabled(false);
                        m_sceneModelRenderableFilter.AddSceneModel(*m_pBoatModel);
                    }
                    
                    void AlcatrazEstablishingShotState::Update(float dt)
                    {
                        if(!m_cameraTransitionComplete && m_toursCameraTransitionController.IsTransitionComplete())
                        {
                            m_cameraTransitionComplete = true;
                            
                            EXAMPLE_LOG("State %s: Camera transition complete.\n", m_stateModel.Headline().c_str());
                        }
                        
                        Helpers::UpdateModel(Eegeo::Space::LatLongAltitude::FromDegrees(37.808886, -122.403506, 0.f),
                                             Eegeo::Space::LatLongAltitude::FromDegrees(37.824322, -122.415499, 0.f),
                                             *m_pBoatModel,
                                             m_pSplineCameraMode->InterpolationState(),
                                             4.f);
                    }
                    
                    void AlcatrazEstablishingShotState::Exit()
                    {
                        m_visualMapService.RestorePreviousMapState();
                        EXAMPLE_LOG("State %s: Exit.\n", m_stateModel.Headline().c_str());
                        
                        m_pAudioPlaybackInstance->Reset();
                        
                        m_placeNamesViewFilter.SetEnabled(true);
                        
                        m_sceneModelRenderableFilter.RemoveSceneModel(*m_pBoatModel);
                    }
                }
            }
        }
    }
}
