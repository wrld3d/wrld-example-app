// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AlcatrazBeginTourState.h"
#include "Logger.h"
#include "LatLongAltitude.h"
#include "IToursCameraTransitionController.h"
#include "TourFullScreenImageCeremonyBeganMessage.h"
#include "TourFullScreenImageCeremonyEndedMessage.h"
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
                    AlcatrazBeginTourState::AlcatrazBeginTourState(const TourStateModel& stateModel,
                                                                   Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                                   VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                                   ExampleAppMessaging::TMessageBus& messageBus)
                    : m_stateModel(stateModel)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_targetCameraMode(Eegeo::Space::LatLongAltitude::FromDegrees(37.7933, -122.389, 1333.99).ToECEF(),
                                   Eegeo::Space::LatLongAltitude::FromDegrees(37.8002, -122.401, 4.83844).ToECEF(),
                                   0.f)
                    , m_cameraTransitionComplete(false)
                    , m_secondCameraTransitionComplete(false)
                    , m_messageBus(messageBus)
                    , m_visualMapService(visualMapService)
                    , m_timeInState(0.f)
                    , m_thirdCameraTransitionStarted(false)
                    {
                        m_positionSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.8112, -122.417, 1279.55).ToECEF());
                        m_positionSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.8224, -122.426, 560.822).ToECEF());
                        m_targetSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.8223, -122.421, -5.0097).ToECEF());
                        m_targetSpline.AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.8266, -122.422, -5.01842).ToECEF());
                        
                        const float startFieldOfViewDegrees(40.f);
                        const float endFieldOfViewDegrees(40.f);
                        const float playbackRateMultiplier(0.15f);
                        
                        m_pSplineCameraMode = Eegeo_NEW(Tours::SdkModel::Camera::SplineCameraMode)(&m_positionSpline,
                                                                                                   &m_targetSpline,
                                                                                                   startFieldOfViewDegrees,
                                                                                                   endFieldOfViewDegrees,
                                                                                                   playbackRateMultiplier);
                        
                    }
                    
                    AlcatrazBeginTourState::~AlcatrazBeginTourState()
                    {
                        Eegeo_DELETE m_pSplineCameraMode;
                    }
                    
                    void AlcatrazBeginTourState::Enter()
                    {
                        EXAMPLE_LOG("State %s: Enter.\n", m_stateModel.Headline().c_str());
                        m_cameraTransitionComplete = false;
                        
                        m_pSplineCameraMode->Reset();
                        m_toursCameraTransitionController.TransitionTo(*m_pSplineCameraMode, false);

                        m_thirdCameraTransitionStarted = false;
                        m_timeInState = 0.f;
                        
                        m_pSplineCameraMode->Reset();
                        
                        m_visualMapService.SetVisualMapState("Summer", "DayDefault", false);
                    }
                    
                    void AlcatrazBeginTourState::Update(float dt)
                    {
                        if(!m_cameraTransitionComplete && m_toursCameraTransitionController.IsTransitionComplete())
                        {
                            if (m_pSplineCameraMode->HasEnded())
                            {
                                m_cameraTransitionComplete = true;
                                
                                m_messageBus.Publish(TourFullScreenImageCeremonyBeganMessage("Tours/States/Alcatraz/intro_hero.jpg",
                                                                                             ""));
                                EXAMPLE_LOG("State %s: Camera transition complete.\n", m_stateModel.Headline().c_str());
                            }
                        }
                        
                        if (m_cameraTransitionComplete && !m_thirdCameraTransitionStarted)
                        {
                            m_timeInState += dt;
                            
                            if (m_timeInState > 1.f)
                            {                 
                                m_toursCameraTransitionController.TransitionTo(m_targetCameraMode, false);
                                m_thirdCameraTransitionStarted = true;
                            }
                        }
                    }
                    
                    void AlcatrazBeginTourState::Exit()
                    {
                        m_visualMapService.RestorePreviousMapState();
                        
                        EXAMPLE_LOG("State %s: Exit.\n", m_stateModel.Headline().c_str());
                        if (m_cameraTransitionComplete)
                        {
                            m_messageBus.Publish(TourFullScreenImageCeremonyEndedMessage());
                        }
                    }
                }
            }
        }
    }
}
