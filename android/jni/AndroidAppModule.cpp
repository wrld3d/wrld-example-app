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
#include "AndroidPersistentSettingsModel.h"
#include "IPersistentSettingsModel.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidAlertBoxFactory.h"
#include "AndroidKeyboardInputFactory.h"
#include "AndroidInputBoxFactory.h"
#include "AndroidMenuReactionModel.h"
#include "IInitialExperienceController.h"
#include "AppInputDelegate.h"
#include "IInputController.h"

namespace
{
	ExampleApp::ApplicationConfig::ApplicationConfiguration LoadApplicationConfiguration(AndroidNativeState& nativeState, const std::set<std::string>& customApplicationAssetDirectories)
	{
		ASSERT_NATIVE_THREAD

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
			m_customApplicationAssetDirectories.insert("SearchResultOnMap");
			m_customApplicationAssetDirectories.insert("ApplicationConfigs");
    	}

    	void AndroidAppModule::Register(const TContainerBuilder& builder)
        {
			std::set<std::string> customApplicationAssetDirectories;
			customApplicationAssetDirectories.insert("SearchResultOnMap");
			customApplicationAssetDirectories.insert("ApplicationConfigs");

    		builder->registerExternallyOwnedInstance(m_nativeState);
    		builder->registerExternallyOwnedInstance(m_screenProperties);
            builder->registerType<ExampleApp::Menu::View::AndroidMenuReactionModel>().as<ExampleApp::Menu::View::IMenuReactionModel>().singleInstance();
    	    builder->registerType<ExampleApp::Metrics::AndroidFlurryMetricsService>().as<ExampleApp::Metrics::IMetricsService>().singleInstance();
            builder->registerType<ExampleApp::InitialExperience::SdkModel::AndroidInitialExperienceModule>().as<ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule>().singleInstance();
            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                             {
                                                 return Hypodermic::makeExternallyOwned(context.resolve<ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule>()->GetInitialExperienceController());
                                             }).singleInstance();
            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
            		{
				 	 	 auto nativeState = context.resolve<AndroidNativeState>();
				 	 	 return std::make_shared<Eegeo::UI::NativeAlerts::Android::AndroidAlertBoxFactory>(nativeState.get());
            		}).as<Eegeo::UI::NativeAlerts::IAlertBoxFactory>().singleInstance();

            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
            		{
				 	 	 auto nativeState = context.resolve<AndroidNativeState>();
						 auto inputHandler = context.resolve<Eegeo::Android::Input::IAndroidInputHandler>();
				 	 	 return std::make_shared<Eegeo::UI::NativeInput::Android::AndroidKeyboardInputFactory>(nativeState.get(), *inputHandler);
            		}).as<Eegeo::UI::NativeInput::IKeyboardInputFactory>().singleInstance();

            builder->registerType<AppInputDelegate>().singleInstance();

            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
            		{
				 	 	 auto nativeState = context.resolve<AndroidNativeState>();
				 	 	 return std::make_shared<Eegeo::UI::NativeInput::Android::AndroidInputBoxFactory>(nativeState.get());
            		}).as<Eegeo::UI::NativeInput::IInputBoxFactory>().singleInstance();

            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
            		{
				 	 	 auto nativeState = context.resolve<AndroidNativeState>();
				 	 	 return std::make_shared<Eegeo::UI::NativeAlerts::Android::AndroidAlertBoxFactory>(nativeState.get());
            		}).as<Eegeo::UI::NativeAlerts::IAlertBoxFactory>().singleInstance();
            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
        			 {
        				 auto nativeState = context.resolve<AndroidNativeState>();
      					 Eegeo_ASSERT(nativeState != nullptr);
        				 return std::make_shared<Eegeo::Android::AndroidLocationService>(nativeState.get());
        			 }).as<Eegeo::Location::ILocationService>().singleInstance();

            builder->registerInstanceFactory([this](Hypodermic::ComponentContext& context)
					 {
						 const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration = LoadApplicationConfiguration(*context.resolve<AndroidNativeState>(), m_customApplicationAssetDirectories);
						 return std::make_shared<ExampleApp::ApplicationConfig::ApplicationConfiguration>(applicationConfiguration);
					 }).singleInstance();

            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
            		{
            			 auto nativeState = context.resolve<AndroidNativeState>();
    					 Eegeo_ASSERT(nativeState != nullptr);
            			 return std::make_shared<Eegeo::Android::AndroidConnectivityService>(nativeState.get());
            		}).as<Eegeo::Web::IConnectivityService>().singleInstance();

			builder->registerType<Eegeo::Android::Input::AndroidInputHandler>().as<Eegeo::Android::Input::IAndroidInputHandler>().singleInstance();
			builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
					{
						auto inputHandler = context.resolve<Eegeo::Android::Input::IAndroidInputHandler>();
						auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
						return std::make_shared<Eegeo::Android::Input::AndroidInputProcessor>(inputHandler.get(), screenProperties->GetScreenWidth(), screenProperties->GetScreenHeight());
					}).singleInstance();

			builder->registerType<PersistentSettings::AndroidPersistentSettingsModel>().as<PersistentSettings::IPersistentSettingsModel>().singleInstance();
			builder->registerInstanceFactory([this](Hypodermic::ComponentContext& context)
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
																								  m_customApplicationAssetDirectories);
					}).as<Eegeo::Modules::IPlatformAbstractionModule>().singleInstance();

        }

    	void AndroidAppModule::RegisterLeaves()
    	{
    		RegisterLeaf<AndroidNativeState>();
    	}
    }
}

