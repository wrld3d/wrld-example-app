// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "AppModule.h"
#include "IAppModeModel.h"
#include "AppModeModel.h"
#include "AppModeStatesFactory.h"
#include "IAppCameraController.h"
#include "AppGlobeCameraWrapper.h"
#include "GpsGlobeCameraController.h"
#include "AppInteriorCameraWrapper.h"
#include "InteriorsCameraController.h"
#include "IToursCameraController.h"
#include "CameraFrustumStreamingVolume.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorTransitionModel.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorsExplorerModel.h"
#include "IVisualMapService.h"
#include "IMetricsService.h"
#include "InteriorExplorerUserInteractionModel.h"
#include "ITourService.h"
#include "NativeUIFactories.h"
#include "IMyPinCreationModel.h"
#include "BiDirectionalBus.h"
#include "SdkModelDomainEventBus.h"
#include "InputController.h"
#include "IPersistentSettingsModel.h"

namespace ExampleApp
{
    void AppModule::Register(const TContainerBuilder& builder)
    {
        builder->registerType<AppModes::SdkModel::AppModeModel>().as<AppModes::SdkModel::IAppModeModel>().singleInstance();
        builder->registerType<AppModes::States::SdkModel::AppModeStatesFactory>().as<AppModes::SdkModel::IAppModeStatesFactory>().singleInstance();
        builder->registerType<ExampleApp::ExampleAppMessaging::TMessageBus>().singleInstance();
        builder->registerType<ExampleApp::ExampleAppMessaging::TSdkModelDomainEventBus>().singleInstance();
        builder->registerType<ExampleApp::InputController>().as<ExampleApp::IInputController>().singleInstance();
    }
}
