// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "AndroidAppModule.h"
#include "AndroidLocationService.h"
#include "AndroidConnectivityService.h"
#include "AndroidInputProcessor.h"
#include "AndroidFlurryMetricsService.h"
#include "ApplicationConfiguration.h"
#include "AndroidInputHandler.h"
#include "AndroidFileIO.h"
#include "ApplicationConfigurationModule.h"
#include "AndroidApplicationConfigurationVersionProvider.h"
#include "ApiKey.h"
#include "AndroidInputHandler.h"
#include "ScreenProperties.h"
#include "NetworkCapabilities.h"
#include "AndroidPlatformAbstractionModule.h"
#include "IJpegLoader.h"
#include "AndroidInitialExperienceModule.h"
#include "IInitialExperienceModule.h"
#include "IWorldAreaLoaderModel.h"
#include "IPersistentSettingsModel.h"
namespace
{
	ExampleApp::ApplicationConfig::ApplicationConfiguration LoadApplicationConfiguration(AndroidNativeState& nativeState, const std::set<std::string>& customApplicationAssetDirectories)
	{
	    Eegeo::Android::AndroidFileIO tempFileIO(&nativeState, customApplicationAssetDirectories);
	    ExampleApp::ApplicationConfig::SdkModel::AndroidApplicationConfigurationVersionProvider versionProvider(nativeState);

	    return ExampleApp::ApplicationConfig::SdkModel::LoadAppConfig(
	    		tempFileIO,
	    		versionProvider,
	    		ExampleApp::ApplicationConfigurationPath);
	}
}

namespace ExampleApp
{
    namespace Android
    {
    	AndroidAppModule::AndroidAppModule(AndroidNativeState& nativeState,
    									   Eegeo::Rendering::ScreenProperties& screenProperties,
    			        				   EGLDisplay& display,
    			        			       EGLSurface& shareSurface,
    			        			       EGLContext& resourceBuildShareContext)
    	: m_nativeState(nativeState)
    	, m_screenProperties(screenProperties)
    	, m_display(display)
    	, m_shareSurface(shareSurface)
    	, m_resourceBuildShareContext(resourceBuildShareContext)
    	{
    	}

    	void AndroidAppModule::Register(const TContainerBuilder& builder)
        {
			std::set<std::string> customApplicationAssetDirectories;
			customApplicationAssetDirectories.insert("SearchResultOnMap");
			customApplicationAssetDirectories.insert("ApplicationConfigs");

    		builder->registerExternallyOwnedInstance(m_nativeState);
    		builder->registerExternallyOwnedInstance(m_screenProperties);

    	    builder->registerType<ExampleApp::Metrics::AndroidFlurryMetricsService>().as<ExampleApp::Metrics::IMetricsService>().singleInstance();
            builder->registerType<ExampleApp::InitialExperience::SdkModel::AndroidInitialExperienceModule>().as<ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule>().singleInstance();

    		builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
    				{
						const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration = LoadApplicationConfiguration(*context.resolve<AndroidNativeState>(), customApplicationAssetDirectories);
						return std::make_shared<ExampleApp::ApplicationConfig::ApplicationConfiguration>(applicationConfiguration);
    				}).singleInstance();

            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
        			 {
        				 auto nativeState = context.resolve<AndroidNativeState>();
        				 return std::make_shared<Eegeo::Android::AndroidLocationService>(nativeState.get());
        			 }).as<Eegeo::Location::ILocationService>().singleInstance();

            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
            		{
            			auto nativeState = context.resolve<AndroidNativeState>();
            			return std::make_shared<Eegeo::Android::AndroidConnectivityService>(nativeState.get());
            		}).as<Eegeo::Web::IConnectivityService>().singleInstance();

			builder->registerType<Eegeo::Android::Input::AndroidInputHandler>().as<Eegeo::Android::Input::IAndroidInputHandler>().singleInstance();
			builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
					{
						auto inputHandler = context.resolve<Eegeo::Android::Input::IAndroidInputHandler>();
						auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
						return std::make_shared<Eegeo::Android::Input::AndroidInputProcessor>(inputHandler.get(), screenProperties->GetScreenWidth(), screenProperties->GetScreenHeight());
					}).singleInstance();

			builder->registerInstanceFactory([&, this](Hypodermic::ComponentContext& context)
					{
			 	 	 	 auto nativeState = context.resolve<AndroidNativeState>();
			 	 	 	 auto jpegLoader = context.resolve<Eegeo::Helpers::Jpeg::IJpegLoader>();
                         auto appConfig = context.resolve<ExampleApp::ApplicationConfig::ApplicationConfiguration>();
						 return std::make_shared<Eegeo::Android::AndroidPlatformAbstractionModule>(*nativeState,
								 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	  *jpegLoader,
																								  m_display,
																								  m_resourceBuildShareContext,
																								  m_shareSurface,
																								  appConfig->EegeoApiKey(),
																								  customApplicationAssetDirectories);
					}).as<Eegeo::Modules::IPlatformAbstractionModule>().singleInstance();

        }
    }
}

