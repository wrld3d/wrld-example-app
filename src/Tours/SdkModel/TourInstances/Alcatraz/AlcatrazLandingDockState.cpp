// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AlcatrazLandingDockState.h"
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
                    AlcatrazLandingDockState::AlcatrazLandingDockState(const TourStateModel& stateModel,
                                                                       Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                                       VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                                       Audio::IAudioPlaybackInstanceFactory& audioPlaybackInstanceFactory,
                                                                       Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                                                       Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter)
                    : m_stateModel(stateModel)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_audioPlaybackInstanceFactory(audioPlaybackInstanceFactory)
                    , m_visualMapService(visualMapService)
                    , m_pAudioPlaybackInstance(m_audioPlaybackInstanceFactory.CreateAudio("Tours/States/Alcatraz/card2.mp3"))
                    , m_sceneModelLoader(sceneModelLoader)
                    , m_sceneModelRenderableFilter(sceneModelRenderableFilter)
                    , m_pBoatModel(NULL)
                    {
                        m_positionSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.8259, -122.413, 417.609).ToECEF());
                        m_positionSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.828, -122.417, 417.605).ToECEF());
                        m_targetSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.825, -122.418, -5.00689).ToECEF());
                        m_targetSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.8271, -122.421, -5.01079).ToECEF());
                        
                        const float startFieldOfViewDegrees(25.f);
                        const float endFieldOfViewDegrees(25.f);
                        const float playbackRateMultiplier(0.12f);
                        
                        m_pSplineCameraMode = Eegeo_NEW(Tours::SdkModel::Camera::SplineCameraMode)(&m_positionSpline,
                                                                                                   &m_targetSpline,
                                                                                                   startFieldOfViewDegrees,
                                                                                                   endFieldOfViewDegrees,
                                                                                                   playbackRateMultiplier);
                        
                        m_positionCraneSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.828, -122.417, 417.605).ToECEF());
                        m_positionCraneSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.8277, -122.416, 546.448).ToECEF());
                        m_targetCraneSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.8271, -122.421, -5.01079).ToECEF());
                        m_targetCraneSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.8268, -122.422, -5.01855 ).ToECEF());
                        
                        m_pCraneCameraMode = Eegeo_NEW(Tours::SdkModel::Camera::SplineCameraMode)(&m_positionCraneSpline,
                                                                                                   &m_targetCraneSpline,
                                                                                                   startFieldOfViewDegrees,
                                                                                                   endFieldOfViewDegrees,
                                                                                                   playbackRateMultiplier);
                        
                        m_pBoatModel = m_sceneModelLoader.LoadPOD("Tours/States/Alcatraz/Boats/Ferry.POD");
                    }
                    
                    AlcatrazLandingDockState::~AlcatrazLandingDockState()
                    {
                        Eegeo_DELETE m_pSplineCameraMode;
                        Eegeo_DELETE m_pCraneCameraMode;
                        Eegeo_DELETE m_pAudioPlaybackInstance;
                        Eegeo_DELETE m_pBoatModel;
                    }
                    
                    void AlcatrazLandingDockState::Enter()
                    {
                        EXAMPLE_LOG("State %s: Enter.\n", m_stateModel.Headline().c_str());
                        m_cameraTransitionComplete = false;
 
                        m_visualMapService.SetVisualMapThemeState("DayFoggy");
                        
                        m_pSplineCameraMode->Reset();
                        m_toursCameraTransitionController.TransitionTo(*m_pSplineCameraMode, false);
                        
                        m_pAudioPlaybackInstance->Reset();
                        m_pAudioPlaybackInstance->Play();
                        
                        m_sceneModelRenderableFilter.AddSceneModel(*m_pBoatModel);
                    }
                    
                    void AlcatrazLandingDockState::Update(float dt)
                    {
                        if(!m_cameraTransitionComplete && m_toursCameraTransitionController.IsTransitionComplete())
                        {
                            if(m_pSplineCameraMode->HasEnded())
                            {
                                m_pCraneCameraMode->Reset();
                                m_toursCameraTransitionController.TransitionTo(*m_pCraneCameraMode, false);
                                m_cameraTransitionComplete = true;
                                
                                EXAMPLE_LOG("State %s: Camera transition complete.\n", m_stateModel.Headline().c_str());
                            }
                            
                        }
                        
                        Helpers::UpdateModel(Eegeo::Space::LatLongAltitude::FromDegrees(37.824322, -122.415499, 0.f),
                                             Eegeo::Space::LatLongAltitude::FromDegrees(37.827167, -122.421274, 0.f),
                                             *m_pBoatModel,
                                             m_pSplineCameraMode->InterpolationState(),
                                             4.f);
                    }
                    
                    void AlcatrazLandingDockState::Exit()
                    {
                        EXAMPLE_LOG("State %s: Exit.\n", m_stateModel.Headline().c_str());
                        
                        m_visualMapService.RestorePreviousMapState();
                        m_pAudioPlaybackInstance->Reset();
                        
                        m_sceneModelRenderableFilter.RemoveSceneModel(*m_pBoatModel);
                    }
                }
            }
        }
    }
}
