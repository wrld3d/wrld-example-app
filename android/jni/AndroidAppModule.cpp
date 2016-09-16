// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "AndroidAppModule.h"
#include "AndroidLocationService.h"
#include "AndroidConnectivityService.h"
#include "AndroidInputProcessor.h"
//#include "iOSAppModule.h"
//#include "iOSLocationService.h"
//#include "iOSConnectivityService.h"
//#include "iOSPersistentSettingsModel.h"
//#include "iOSInitialExperienceModule.h"
//#include "IInitialExperienceModule.h"
//#include "LinkOutObserver.h"
//#include "URLRequestHandler.h"
//#include "IOSMenuReactionModel.h"
//#include "iOSPlatformConfigBuilder.h"
//#include "PlatformConfig.h"
//#include "AppLocationDelegate.h"
//#include "App.h"
//#include "ApplicationConfigurationModule.h"
//#include "IWorldAreaLoaderModel.h"
//#include "IInitialExperienceController.h"

namespace ExampleApp
{
    namespace Android
    {
    	AndroidAppModule::AndroidAppModule(
//                                   Eegeo::Rendering::ScreenProperties screenProperties,
//                                   ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
//                                   ExampleApp::Metrics::iOSFlurryMetricsService& metricsService
    									Eegeo::Android::AndroidLocationService& androidLocationService,
    			            		   	Eegeo::Android::AndroidConnectivityService& androidConnectivityService,
										Eegeo::Android::Input::AndroidInputProcessor& androidInputProcessor)
        : m_pAndroidLocationService(androidLocationService)
        , m_pAndroidConnectivityService(androidConnectivityService)
    	, m_pAndroidInputProcessor(androidInputProcessor)
        {
        }
    	void AndroidAppModule::Register(const TContainerBuilder& builder)
        {
            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
        			 {
        				 auto nativeState = context.resolve<AndroidNativeState>();
        				 return std::make_shared<AndroidLocationService>(nativeState.get());
        			 }).as<ILocationService>().singleInstance();

            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context))
            		{
            			auto nativeState = context.resolve<AndroidNativeState>();
            			return std::make_shared<AndroidConnectivityService>(nativeState.get());
            		}).as<IConnectivityService>().singleInstance();

			builder->registerType<AndroidInputHandler>().as<IAndroidInputHandler>().singleInstance();
			builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
					{
						auto inputHandler = context.resolve<IAndroidInputHandler>();
						auto screenProperties = contexgt.resolve<Eegeo::Rendering::ScreenProperties>();
						return std::make_shared<Eegeo::Android::Input::AndroidInputProcessor>(inputHandler.get(), screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());
					}).singleInstance();
//            builder->registerExternallyOwnedInstance(m_metricsService).as<ExampleApp::Metrics::IMetricsService>();
//            builder->registerExternallyOwnedInstance(m_screenProperties);
//            builder->registerExternallyOwnedInstance(m_applicationConfiguration);
//            builder->registerType<Eegeo::iOS::iOSLocationService>().as<Eegeo::Location::ILocationService>().singleInstance();
//
//            builder->registerType<Eegeo::iOS::iOSConnectivityService>().as<Eegeo::Web::IConnectivityService>().singleInstance();
//            builder->registerType<ExampleApp::PersistentSettings::iOSPersistentSettingsModel>().as<ExampleApp::PersistentSettings::IPersistentSettingsModel>().singleInstance();
//            builder->registerType<ExampleApp::InitialExperience::iOSInitialExperienceModule>().as<ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule>().singleInstance();
//            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
//                                             {
//                                                 return Hypodermic::makeExternallyOwned(context.resolve<ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule>()->GetInitialExperienceController());
//                                             }).singleInstance();
//            builder->registerType<ExampleApp::LinkOutObserver::LinkOutObserver>().singleInstance();
//            builder->registerType<ExampleApp::URLRequest::View::URLRequestHandler>().singleInstance();
//            builder->registerType<ExampleApp::Menu::View::IOSMenuReactionModel>().as<ExampleApp::Menu::View::IMenuReactionModel>().singleInstance();
//            builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
//                                             {
//                                                 Eegeo::iOS::iOSPlatformConfigBuilder iOSPlatformConfigBuilder(App::GetDevice(), App::IsDeviceMultiCore(), App::GetMajorSystemVersion());
//                                                 return std::make_shared<Eegeo::Config::PlatformConfig>(ExampleApp::ApplicationConfig::SdkModel::BuildPlatformConfig(iOSPlatformConfigBuilder, *context.resolve<ExampleApp::ApplicationConfig::ApplicationConfiguration>()));
//
//                                             }).singleInstance();
//            builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
//                                             {
//                                                 auto locationService = context.resolve<Eegeo::Location::ILocationService>();
//                                                 return std::make_shared<AppLocationDelegate>(locationService, m_viewController);
//                                             }).singleInstance();
//            builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
//                                             {
//                                                 return std::make_shared<ViewControllerWrapper>(&m_viewController);
//                                             }).singleInstance();
        }
    }
}

