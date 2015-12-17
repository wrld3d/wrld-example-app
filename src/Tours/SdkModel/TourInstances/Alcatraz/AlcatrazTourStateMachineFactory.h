// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ITourStateMachine.h"
#include "Tours.h"
#include "PlaceNamesViewFilter.h"
#include "Geofencing.h"
#include "Pins.h"
#include "WorldPins.h"
#include "BidirectionalBus.h"
#include "IFlattenButtonModel.h"
#include "Routes.h"
#include "IFileIO.h"
#include "FireworksModule.h"
#include "WeatherMenu.h"
#include "Roads.h"
#include "Audio.h"
#include "Rendering.h"
#include "GlobeCamera.h"
#include "Metrics.h"
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
                    class AlcatrazTourStateMachineFactory : private Eegeo::NonCopyable
                    {
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        Camera::IToursCameraController& m_toursCameraController;
                        Eegeo::Data::Geofencing::GeofenceController& m_geofenceController;
                        WorldPins::SdkModel::IWorldPinsService& m_toursWorldPinsService;
                        FlattenButton::SdkModel::IFlattenButtonModel& m_flattenButtonModel;
                        Eegeo::Routes::RouteService& m_routeService;
                        ExampleAppMessaging::TMessageBus& m_messageBus;
                        Eegeo::Modules::FireworksModule& m_fireworksModule;
                        WeatherMenu::SdkModel::IWeatherController& m_weatherController;
                        Eegeo::Resources::Roads::RoadNamesFadeController& m_roadNamesController;
                        Audio::IAudioPlaybackInstanceFactory& m_audioPlaybackInstanceFactory;
                        Eegeo::Rendering::SceneModels::SceneModelLoader& m_sceneModelLoader;
                        Eegeo::Rendering::Filters::SceneModelRenderableFilter& m_sceneModelRenderableFilter;
                        Eegeo::Resources::PlaceNames::PlaceNamesViewFilter& m_placeNamesViewFilter;
                        WorldPins::SdkModel::IWorldPinsInFocusController& m_worldPinsInFocusController;
                        VisualMap::SdkModel::IVisualMapService& m_visualMapService;
                        
                        const Eegeo::Rendering::ScreenProperties& m_screenProperties;
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_touchController;
                        Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory& m_cameraControllerFactory;
                        
                        Metrics::IMetricsService& m_metricsService;
                        
                    public:
                        AlcatrazTourStateMachineFactory(Camera::IToursCameraTransitionController& toursCameraTransitionController,
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
                                                        Metrics::IMetricsService& metricsService);
                        
                        ~AlcatrazTourStateMachineFactory();
                        
                        States::ITourStateMachine* CreateTourStateMachine(const TourModel& tourModel);
                    };
                }
            }
        }
    }
}
