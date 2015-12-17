// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AlcatrazTourStateMachineFactory.h"
#include "TourStateMachine.h"
#include "TourModel.h"
#include "AlcatrazRecreationYardState.h"
#include "AlcatrazLandingDockState.h"
#include "AlcatrazEstablishingShotState.h"
#include "AlcatrazCellHouseIntroState.h"
#include "AlcatrazCellHouseDetailState.h"
#include "AlcatrazIsolatorState.h"
#include "AlcatrazBeginTourState.h"
#include "AlcatrazDownloadGuidekickAppState.h"

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
                    AlcatrazTourStateMachineFactory::AlcatrazTourStateMachineFactory(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                                                     Camera::IToursCameraController& toursCameraController,
                                                                                     Eegeo::Data::Geofencing::GeofenceController& geofenceController,
                                                                                     WorldPins::SdkModel::IWorldPinsService& toursWorldPinsService,
                                                                                     FlattenButton::SdkModel::IFlattenButtonModel& flattenButtonModel,
                                                                                     Eegeo::Routes::RouteService& routeService,
                                                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                                                     WeatherMenu::SdkModel::IWeatherController& weatherController,
                                                                                     Eegeo::Modules::FireworksModule& fireworksModule,
                                                                                     Eegeo::Resources::Roads::RoadNamesFadeController& roadNamesController,
                                                                                     Audio::IAudioPlaybackInstanceFactory& audioPlaybackInstanceFactory,
                                                                                     Eegeo::Resources::PlaceNames::PlaceNamesViewFilter& placeNamesViewFilter,
                                                                                     Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                                                                     Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter,
                                                                                     WorldPins::SdkModel::IWorldPinsInFocusController& worldPinsInFocusController,
                                                                                     const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                                                     Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                                                                     Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory& cameraControllerFactory,
                                                                                     VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                                                     Metrics::IMetricsService& metricsService)
                    : m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_toursCameraController(toursCameraController)
                    , m_geofenceController(geofenceController)
                    , m_toursWorldPinsService(toursWorldPinsService)
                    , m_flattenButtonModel(flattenButtonModel)
                    , m_routeService(routeService)
                    , m_messageBus(messageBus)
                    , m_weatherController(weatherController)
                    , m_fireworksModule(fireworksModule)
                    , m_roadNamesController(roadNamesController)
                    , m_audioPlaybackInstanceFactory(audioPlaybackInstanceFactory)
                    , m_placeNamesViewFilter(placeNamesViewFilter)
                    , m_sceneModelLoader(sceneModelLoader)
                    , m_sceneModelRenderableFilter(sceneModelRenderableFilter)
                    , m_worldPinsInFocusController(worldPinsInFocusController)
                    , m_screenProperties(screenProperties)
                    , m_touchController(touchController)
                    , m_cameraControllerFactory(cameraControllerFactory)
                    , m_visualMapService(visualMapService)
                    , m_metricsService(metricsService)
                    {
                    }
                    
                    AlcatrazTourStateMachineFactory::~AlcatrazTourStateMachineFactory()
                    {
                    }
                    
                    States::ITourStateMachine* AlcatrazTourStateMachineFactory::CreateTourStateMachine(const TourModel& tourModel)
                    {
                        // These states must be dynamically allocated, they will become owned by
                        // TourStateMachine, which will Eegeo_DELETE them when it is destroyed.
                        
                        std::vector<States::ITourStateMachineState*> stateMachineStates;
                        
                        Eegeo_ASSERT(tourModel.States().size() == 7); // Sanity check while testing.
                        
                        int tourIndex = 0;
                        
                        stateMachineStates.push_back(Eegeo_NEW(AlcatrazBeginTourState(tourModel.States()[tourIndex++],
                                                                                      m_toursCameraTransitionController,
                                                                                      m_visualMapService,
                                                                                      m_messageBus)));
                        
                        stateMachineStates.push_back(Eegeo_NEW(AlcatrazEstablishingShotState(tourModel.States()[tourIndex++],
                                                                                             m_toursCameraTransitionController,
                                                                                             m_visualMapService,
                                                                                             m_placeNamesViewFilter,
                                                                                             m_audioPlaybackInstanceFactory,
                                                                                             m_sceneModelLoader,
                                                                                             m_sceneModelRenderableFilter)));
                        
                        stateMachineStates.push_back(Eegeo_NEW(AlcatrazLandingDockState(tourModel.States()[tourIndex++],
                                                                                        m_toursCameraTransitionController,
                                                                                        m_visualMapService,
                                                                                        m_audioPlaybackInstanceFactory,
                                                                                        m_sceneModelLoader,
                                                                                        m_sceneModelRenderableFilter)));
                        
                        stateMachineStates.push_back(Eegeo_NEW(AlcatrazCellHouseIntroState)(tourModel.States()[tourIndex++],
                                                                                            m_toursCameraTransitionController,
                                                                                            m_audioPlaybackInstanceFactory,
                                                                                            m_sceneModelLoader,
                                                                                            m_sceneModelRenderableFilter,
                                                                                            m_visualMapService,
                                                                                            m_toursWorldPinsService,
                                                                                            m_messageBus,
                                                                                            m_screenProperties,
                                                                                            m_touchController,
                                                                                            m_cameraControllerFactory));
                        
                        stateMachineStates.push_back(Eegeo_NEW(AlcatrazCellHouseDetailState(tourModel.States()[tourIndex++],
                                                                                            m_toursCameraTransitionController,
                                                                                            m_audioPlaybackInstanceFactory,
                                                                                            m_visualMapService,
                                                                                            m_messageBus,
                                                                                            m_screenProperties,
                                                                                            m_touchController,
                                                                                            m_cameraControllerFactory)));
                        
                        stateMachineStates.push_back(Eegeo_NEW(AlcatrazRecreationYardState(tourModel.States()[tourIndex++],
                                                                                           m_toursCameraTransitionController,
                                                                                           m_visualMapService,
                                                                                           m_audioPlaybackInstanceFactory,
                                                                                           m_toursWorldPinsService,
                                                                                           m_messageBus,
                                                                                           m_screenProperties,
                                                                                           m_touchController,
                                                                                           m_cameraControllerFactory)));
                        
                        stateMachineStates.push_back(Eegeo_NEW(AlcatrazDownloadGuidekickAppState(tourModel.States()[tourIndex++],
                                                                                                 m_toursCameraTransitionController,
                                                                                                 m_toursWorldPinsService,
                                                                                                 m_messageBus,
                                                                                                 m_metricsService)));
                        
                        States::ITourStateMachineState* pTourSetupTeardownState = Eegeo_NEW(AlcatrazIsolatorState)(m_roadNamesController);
                        
                        return Eegeo_NEW(States::TourStateMachine)(stateMachineStates,
                                                                   pTourSetupTeardownState);
                    }
                }
            }
        }
    }
}
