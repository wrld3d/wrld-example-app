// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AlcatrazCellHouseIntroState.h"
#include "Logger.h"
#include "IToursCameraTransitionController.h"
#include "LatLongAltitude.h"
#include "IAudioPlaybackInstanceFactory.h"
#include "IAudioPlaybackInstance.h"
#include "SceneModelLoader.h"
#include "SceneModel.h"
#include "SceneModelRenderableFilter.h"
#include "AlcatrazTourHelpers.h"
#include "LatLongAltitude.h"
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
                    AlcatrazCellHouseIntroState::AlcatrazCellHouseIntroState(const TourStateModel& stateModel,
                                                                             Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                                             Audio::IAudioPlaybackInstanceFactory& audioPlaybackInstanceFactory,
                                                                             Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                                                             Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter,
                                                                             VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                                             WorldPins::SdkModel::IWorldPinsService& toursWorldPinsService,
                                                                             ExampleAppMessaging::TMessageBus& messageBus,
                                                                             const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                                             Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                                                             Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory& cameraControllerFactory)
                    : m_stateModel(stateModel)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_audioPlaybackInstanceFactory(audioPlaybackInstanceFactory)
                    , m_pAudioPlaybackInstance(m_audioPlaybackInstanceFactory.CreateAudio("Tours/States/Alcatraz/card3.mp3"))
                    , m_sceneModelLoader(sceneModelLoader)
                    , m_sceneModelRenderableFilter(sceneModelRenderableFilter)
                    , m_cameraMode(Eegeo::Space::LatLong::FromDegrees(37.826808, -122.422523),
                                   Eegeo::Space::LatLongAltitude::FromDegrees(37.829433, -122.427614, Camera::DefaultMapCameraModeMaxAltitude),
                                   Eegeo::Space::LatLongAltitude::FromDegrees(37.823866, -122.416917, Camera::DefaultMapCameraModeMinAltitude),
                                   500,
                                   25.0f,
                                   0.0f,
                                   screenProperties,
                                   touchController,
                                   cameraControllerFactory,
                                   false)
                    , m_pBoatModel(NULL)
                    , m_visualMapService(visualMapService)
                    , m_timeInState(0.f)
                    , m_toursWorldPinsService(toursWorldPinsService)
                    , m_messageBus(messageBus)
                    {   
                        m_pBoatModel = m_sceneModelLoader.LoadPOD("Tours/States/Alcatraz/Boats/Ferry.POD");
                    }
                    
                    AlcatrazCellHouseIntroState::~AlcatrazCellHouseIntroState()
                    {
                        Eegeo_DELETE m_pAudioPlaybackInstance;
                        Eegeo_DELETE m_pBoatModel;
                    }
                    
                    void AlcatrazCellHouseIntroState::Enter()
                    {
                        m_timeInState = 0.f;
                        EXAMPLE_LOG("State %s: Enter.\n", m_stateModel.Headline().c_str());
                        m_cameraTransitionComplete = false;
                        
                        m_cameraMode.Reset();
                        m_toursCameraTransitionController.TransitionTo(m_cameraMode, false);
                        
                        
                        m_pAudioPlaybackInstance->Reset();
                        m_pAudioPlaybackInstance->Play();
                        
                        m_sceneModelRenderableFilter.AddSceneModel(*m_pBoatModel);

                        m_visualMapService.SetVisualMapThemeState("DayRainy");
                        
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
                    
                    void AlcatrazCellHouseIntroState::Update(float dt)
                    {
                        if(!m_cameraTransitionComplete && m_toursCameraTransitionController.IsTransitionComplete())
                        {
                            m_cameraTransitionComplete = true;
                            
                            EXAMPLE_LOG("State %s: Camera transition complete.\n", m_stateModel.Headline().c_str());
                        }

                        m_timeInState += dt;
                        
                        const Eegeo::Space::LatLongAltitude oldEnd(Eegeo::Space::LatLongAltitude::FromDegrees(37.832395, -122.429090, 0.f));
                        const Eegeo::Space::LatLongAltitude start(Eegeo::Space::LatLongAltitude::FromDegrees(37.827167, -122.421274, 0.f));
                        const float extraDistanceMeters(300.f);
                        const Eegeo::Space::LatLongAltitude end(Eegeo::Space::LatLongAltitude::FromECEF(oldEnd.ToECEF() + ((oldEnd.ToECEF() - start.ToECEF()).ToSingle().Norm() * extraDistanceMeters)));
                        
                        Helpers::UpdateModel(start,
                                             end,
                                             *m_pBoatModel,
                                             Eegeo::Math::Clamp01(m_timeInState / 14.f),
                                             4.f);
                    }
                    
                    void AlcatrazCellHouseIntroState::Exit()
                    {
                        EXAMPLE_LOG("State %s: Exit.\n", m_stateModel.Headline().c_str());
                        
                        m_pAudioPlaybackInstance->Reset();
                        
                        m_sceneModelRenderableFilter.RemoveSceneModel(*m_pBoatModel);
                        
                        m_visualMapService.RestorePreviousMapState();
                        
                        Helpers::RemovePins(m_alcatrazSharedTourPins, m_toursWorldPinsService);
                    }
                }
            }
        }
    }
}
