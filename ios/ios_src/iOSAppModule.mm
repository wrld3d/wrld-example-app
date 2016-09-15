// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "iOSAppModule.h"
#include "iOSLocationService.h"
#include "iOSConnectivityService.h"
#include "iOSPersistentSettingsModel.h"
#include "iOSInitialExperienceModule.h"
#include "IInitialExperienceModule.h"
#include "LinkOutObserver.h"
#include "URLRequestHandler.h"
#include "IOSMenuReactionModel.h"
#include "iOSPlatformConfigBuilder.h"
#include "PlatformConfig.h"
#include "AppLocationDelegate.h"
#include "App.h"
#include "ApplicationConfigurationModule.h"
#include "IWorldAreaLoaderModel.h"
#include "IInitialExperienceController.h"

namespace ExampleApp
{
    namespace iOS
    {
        iOSAppModule::iOSAppModule(
                                   Eegeo::Rendering::ScreenProperties screenProperties,
                                   ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
                                   ExampleApp::Metrics::iOSFlurryMetricsService& metricsService,
                                   ViewController& viewController)
        : m_screenProperties(screenProperties)
        , m_applicationConfiguration(applicationConfiguration)
        , m_metricsService(metricsService)
        , m_viewController(viewController)
        {
        }
        
        void iOSAppModule::Register(const ExampleApp::TContainerBuilder& builder)
        {
            builder->registerExternallyOwnedInstance(m_metricsService).as<ExampleApp::Metrics::IMetricsService>();
            builder->registerExternallyOwnedInstance(m_screenProperties);
            builder->registerExternallyOwnedInstance(m_applicationConfiguration);
            builder->registerType<Eegeo::iOS::iOSLocationService>().as<Eegeo::Location::ILocationService>().singleInstance();
            builder->registerType<Eegeo::iOS::iOSConnectivityService>().as<Eegeo::Web::IConnectivityService>().singleInstance();
            builder->registerType<ExampleApp::PersistentSettings::iOSPersistentSettingsModel>().as<ExampleApp::PersistentSettings::IPersistentSettingsModel>().singleInstance();
            builder->registerType<ExampleApp::InitialExperience::iOSInitialExperienceModule>().as<ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule>().singleInstance();
            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                             {
                                                 return Hypodermic::makeExternallyOwned(context.resolve<ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule>()->GetInitialExperienceController());
                                             }).singleInstance();
            builder->registerType<ExampleApp::LinkOutObserver::LinkOutObserver>().singleInstance();
            builder->registerType<ExampleApp::URLRequest::View::URLRequestHandler>().singleInstance();
            builder->registerType<ExampleApp::Menu::View::IOSMenuReactionModel>().as<ExampleApp::Menu::View::IMenuReactionModel>().singleInstance();
            builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
                                             {
                                                 Eegeo::iOS::iOSPlatformConfigBuilder iOSPlatformConfigBuilder(App::GetDevice(), App::IsDeviceMultiCore(), App::GetMajorSystemVersion());
                                                 return std::make_shared<Eegeo::Config::PlatformConfig>(ExampleApp::ApplicationConfig::SdkModel::BuildPlatformConfig(iOSPlatformConfigBuilder, *context.resolve<ExampleApp::ApplicationConfig::ApplicationConfiguration>()));
                                                 
                                             }).singleInstance();
            builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
                                             {
                                                 auto locationService = context.resolve<Eegeo::Location::ILocationService>();
                                                 return std::make_shared<AppLocationDelegate>(locationService, m_viewController);
                                             }).singleInstance();
            builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
                                             {
                                                 return std::make_shared<ViewControllerWrapper>(&m_viewController);
                                             }).singleInstance();
        }
    }
}

