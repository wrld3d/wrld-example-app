// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppCameraModule.h"
#include "AppCameraController.h"
#include "GpsGlobeCameraController.h"
#include "AppGlobeCameraWrapper.h"
#include "CameraTransitionService.h"
#include "CameraTransitionController.h"
#include "GpsGlobeCameraComponentConfiguration.h"
#include "NavigationService.h"
#include "ResourceCeilingProvider.h"
#include "EnvironmentFlatteningService.h"
#include "TerrainHeightProvider.h"
#include "GpsGlobeCameraControllerFactory.h"
#include "GlobeCameraTouchControllerConfiguration.h"
#include "GlobeCameraControllerConfiguration.h"
#include "DoubleTapIndoorInteractionController.h"
#include "AppInteriorCameraWrapper.h"
#include "ScreenProperties.h"
#include "InteriorsCameraController.h"
#include "IInteriorsNavigationService.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorTransitionModel.h"
#include "InteriorsExplorerModel.h"
#include "IVisualMapService.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            void AppCameraModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       Eegeo::Camera::GlobeCamera::GpsGlobeCameraControllerFactory cameraControllerFactory(*(context.resolve<Eegeo::Resources::Terrain::Heights::TerrainHeightProvider>()),
                                                                                                                                           *(context.resolve<Eegeo::Rendering::EnvironmentFlatteningService>()),
                                                                                                                                           *(context.resolve<Eegeo::Streaming::ResourceCeilingProvider>()),
                                                                                                                                           *(context.resolve<Eegeo::Location::NavigationService>()));
                                                       
                                                       const bool useLowSpecSettings = false;
                                                       
                                                       Eegeo::Camera::GlobeCamera::GpsGlobeCameraComponentConfiguration gpsGlobeCameraConfig = Eegeo::Camera::GlobeCamera::GpsGlobeCameraComponentConfiguration::CreateDefault();
                                                       gpsGlobeCameraConfig.panToUnlockThreshold =  0.03f;
                                                       Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchControllerConfig = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
                                                       Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration globeCameraConfig = Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration::CreateDefault(useLowSpecSettings);
                                                       
                                                       Eegeo::Camera::GlobeCamera::GpsGlobeCameraController* pGlobeCameraController = cameraControllerFactory.Create(gpsGlobeCameraConfig, touchControllerConfig, globeCameraConfig,
                                                                                                                                                                     *(context.resolve<Eegeo::Rendering::ScreenProperties>()));
                                                       return std::shared_ptr<Eegeo::Camera::GlobeCamera::GpsGlobeCameraController>(pGlobeCameraController);
                                                   }).singleInstance();
                
                builder->registerType<ExampleApp::AppCamera::SdkModel::AppGlobeCameraWrapper>().as<ExampleApp::AppCamera::SdkModel::IAppCamera>().singleInstance();
                builder->registerType<ExampleApp::CameraTransitions::SdkModel::CameraTransitionService>().as<ExampleApp::CameraTransitions::SdkModel::ICameraTransitionController>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return Hypodermic::makeExternallyOwned(context.resolve<ExampleApp::AppCamera::SdkModel::AppGlobeCameraWrapper>()->GetTouchController());
                                                   }).singleInstance();
                builder->registerType<ExampleApp::CameraTransitions::SdkModel::CameraTransitionController>().singleInstance();
                builder->registerType<AppCamera::SdkModel::AppCameraController>().as<AppCamera::SdkModel::IAppCameraController>().singleInstance();
                builder->registerType<DoubleTapIndoorInteraction::SdkModel::DoubleTapIndoorInteractionController>().as<DoubleTapIndoorInteraction::SdkModel::IDoubleTapIndoorInteractionController>().singleInstance();
                builder->registerType<AppCamera::SdkModel::AppInteriorCameraWrapper>().singleInstance();
            }
        }
    }
}
