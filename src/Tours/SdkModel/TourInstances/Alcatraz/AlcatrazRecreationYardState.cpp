// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AlcatrazRecreationYardState.h"
#include "Logger.h"
#include "IToursCameraTransitionController.h"
#include "LatLongAltitude.h"
#include "IAudioPlaybackInstanceFactory.h"
#include "IAudioPlaybackInstance.h"
#include "AlcatrazTourHelpers.h"
#include "AlcatrazTourConstants.h"
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
                    AlcatrazRecreationYardState::AlcatrazRecreationYardState(const TourStateModel& stateModel,
                                                                             Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                                             VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                                             Audio::IAudioPlaybackInstanceFactory& audioPlaybackInstanceFactory,
                                                                             WorldPins::SdkModel::IWorldPinsService& toursWorldPinsService,
                                                                             ExampleAppMessaging::TMessageBus& messageBus,
                                                                             const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                                             Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                                                             Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory& cameraControllerFactory)
                    : m_stateModel(stateModel)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_visualMapService(visualMapService)
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
                    , m_pAudioPlaybackInstance(m_audioPlaybackInstanceFactory.CreateAudio("Tours/States/Alcatraz/card5.mp3"))
                    , m_toursWorldPinsService(toursWorldPinsService)
                    , m_messageBus(messageBus)
                    {
                        
                    }
                    
                    AlcatrazRecreationYardState::~AlcatrazRecreationYardState()
                    {
                        Eegeo_DELETE m_pAudioPlaybackInstance;
                    }
                    
                    void AlcatrazRecreationYardState::Enter()
                    {
                        EXAMPLE_LOG("State %s: Enter.\n", m_stateModel.Headline().c_str());
                    m_visualMapService.SetVisualMapThemeState("DayDefault");
                        
                        m_cameraTransitionComplete = false;
                        m_cameraMode.Reset();
                        m_toursCameraTransitionController.TransitionTo(m_cameraMode, false);
                        
                        m_pAudioPlaybackInstance->Reset();
                        m_pAudioPlaybackInstance->Play();
                        
                        m_alcatrazSharedTourPins.push_back(Helpers::CreatePin("Recreation Yard",
                                                                              RecreationYardInfoText,
                                                                              Eegeo::Space::LatLongAltitude::FromDegrees(37.827082, -122.423741, 25.f),
                                                                              false,
                                                                              m_toursWorldPinsService,
                                                                              WorldPins::SdkModel::WorldPinInteriorData(),
                                                                              m_messageBus,
                                                                              true,
                                                                              "Tours/States/Alcatraz/Pins/rec_yard_pin.jpg"));
                        
                        
                        m_alcatrazSharedTourPins.push_back(Helpers::CreatePin("Cell House",
                                                                              CellHouseInfoText,
                                                                              Eegeo::Space::LatLongAltitude::FromDegrees(37.826662, -122.422893, 0.f),
                                                                              false,
                                                                              m_toursWorldPinsService,
                                                                              WorldPins::SdkModel::WorldPinInteriorData(),
                                                                              m_messageBus,
                                                                              true,
                                                                              "Tours/States/Alcatraz/Pins/cell_house_pin.jpg"));
                        
                        m_alcatrazSharedTourPins.push_back(Helpers::CreatePin("Parade Ground",
                                                                              ParadeGroundInfoText,
                                                                              Eegeo::Space::LatLongAltitude::FromDegrees(37.825870, -122.421558, 0.f),
                                                                              false,
                                                                              m_toursWorldPinsService,
                                                                              WorldPins::SdkModel::WorldPinInteriorData(),
                                                                              m_messageBus,
                                                                              true,
                                                                              "Tours/States/Alcatraz/Pins/parade_ground_pin.jpg"));
                        
                        m_alcatrazSharedTourPins.push_back(Helpers::CreatePin("Landing Dock",
                                                                              LandingDockInfoText,
                                                                              Eegeo::Space::LatLongAltitude::FromDegrees(37.826832, -122.421316, 0.f),
                                                                              false,
                                                                              m_toursWorldPinsService,
                                                                              WorldPins::SdkModel::WorldPinInteriorData(),
                                                                              m_messageBus,
                                                                              true,
                                                                              "Tours/States/Alcatraz/Pins/landing_dock_pin.jpg"));
                    }
                    
                    void AlcatrazRecreationYardState::Update(float dt)
                    {
                        if(!m_cameraTransitionComplete && m_toursCameraTransitionController.IsTransitionComplete())
                        {
                            m_cameraTransitionComplete = true;
                            
                            EXAMPLE_LOG("State %s: Camera transition complete.\n", m_stateModel.Headline().c_str());
                        }
                    }
                    
                    void AlcatrazRecreationYardState::Exit()
                    {
                        EXAMPLE_LOG("State %s: Exit.\n", m_stateModel.Headline().c_str());
                        
                        m_visualMapService.RestorePreviousMapState();
                        m_pAudioPlaybackInstance->Reset();
                        
                        Helpers::RemovePins(m_alcatrazSharedTourPins, m_toursWorldPinsService);
                    }
                }
            }
        }
    }
}
