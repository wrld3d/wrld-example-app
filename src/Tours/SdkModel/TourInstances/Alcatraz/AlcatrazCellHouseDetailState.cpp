// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AlcatrazCellHouseDetailState.h"
#include "Logger.h"
#include "IToursCameraTransitionController.h"
#include "LatLongAltitude.h"
#include "IAudioPlaybackInstanceFactory.h"
#include "IAudioPlaybackInstance.h"
#include "AlcatrazTourHelpers.h"
#include "WorldPinInteriorData.h"
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
                    AlcatrazCellHouseDetailState::AlcatrazCellHouseDetailState(const TourStateModel& stateModel,
                                                                               Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                                               Audio::IAudioPlaybackInstanceFactory& audioPlaybackInstanceFactory,
                                                                               VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                                                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                                               const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                                               Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                                                               Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory& cameraControllerFactory)
                    : m_stateModel(stateModel)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_cameraMode(Eegeo::Space::LatLong::FromDegrees(37.827082, -122.423741),
                                   Eegeo::Space::LatLongAltitude::FromDegrees(37.829433, -122.427614, Camera::DefaultMapCameraModeMaxAltitude),
                                   Eegeo::Space::LatLongAltitude::FromDegrees(37.823866, -122.416917, Camera::DefaultMapCameraModeMinAltitude),
                                   200,
                                   25.0f,
                                   0.0f,
                                   screenProperties,
                                   touchController,
                                   cameraControllerFactory,
                                   false)
                    , m_audioPlaybackInstanceFactory(audioPlaybackInstanceFactory)
                    , m_pAudioPlaybackInstance(m_audioPlaybackInstanceFactory.CreateAudio("Tours/States/Alcatraz/card4.mp3"))
                    , m_visualMapService(visualMapService)
                    , m_messageBus(messageBus)
                    {
                    }
                    
                    AlcatrazCellHouseDetailState::~AlcatrazCellHouseDetailState()
                    {
                        Eegeo_DELETE m_pAudioPlaybackInstance;
                    }
                    
                    void AlcatrazCellHouseDetailState::Enter()
                    {
                        m_heroCardInYourFace = false;
                        EXAMPLE_LOG("State %s: Enter.\n", m_stateModel.Headline().c_str());
                        m_cameraTransitionComplete = false;
                        m_cameraMode.Reset();
                        m_toursCameraTransitionController.TransitionTo(m_cameraMode, false);
                        
                        m_visualMapService.SetVisualMapThemeState("DayDefault");
                        
                        m_pAudioPlaybackInstance->Reset();
                        m_pAudioPlaybackInstance->Play();
                        
                    }
                    
                    void AlcatrazCellHouseDetailState::Update(float dt)
                    {
                        
                        if (!m_heroCardInYourFace)
                        {
                            m_heroCardInYourFace = true;
                            
                            m_messageBus.Publish(TourFullScreenImageCeremonyBeganMessage("Tours/States/Alcatraz/full_hero.jpg",
                                                                                         ""));
                        }
                        
                        if(!m_cameraTransitionComplete && m_toursCameraTransitionController.IsTransitionComplete())
                        {
                            m_cameraTransitionComplete = true;
                            
                            EXAMPLE_LOG("State %s: Camera transition complete.\n", m_stateModel.Headline().c_str());
                        }
                    }
                    
                    void AlcatrazCellHouseDetailState::Exit()
                    {
                        EXAMPLE_LOG("State %s: Exit.\n", m_stateModel.Headline().c_str());
                        if (m_heroCardInYourFace)
                        {
                            m_messageBus.Publish(TourFullScreenImageCeremonyEndedMessage());
                        }
                        
                        m_visualMapService.RestorePreviousMapState();
                        m_pAudioPlaybackInstance->Reset();
                    }
                }
            }
        }
    }
}
