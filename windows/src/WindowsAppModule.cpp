// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "WindowsAppModule.h"
#include "WindowsLocationService.h"
#include "WindowsConnectivityService.h"
#include "WindowsInputProcessor.h"
#include "WindowsFlurryMetricsService.h"
#include "ApplicationConfiguration.h"
#include "WindowsInputHandler.h"
#include "WindowsFileIO.h"
#include "ApplicationConfigurationModule.h"
#include "WindowsApplicationConfigurationVersionProvider.h"
#include "ApiKey.h"
#include "WindowsInputHandler.h"
#include "ScreenProperties.h"
#include "NetworkCapabilities.h"
#include "WindowsPlatformAbstractionModule.h"
#include "IJpegLoader.h"
#include "WindowsInitialExperienceModule.h"
#include "IInitialExperienceModule.h"
#include "IWorldAreaLoaderModel.h"
#include "WindowsPersistentSettingsModel.h"
#include "IPersistentSettingsModel.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "WindowsAlertBoxFactory.h"
#include "WindowsKeyboardInputFactory.h"
#include "WindowsInputBoxFactory.h"
#include "WindowsMenuReactionModel.h"
#include "IInitialExperienceController.h"
#include "AppInputDelegate.h"
#include "IInputController.h"

namespace
{
    ExampleApp::ApplicationConfig::ApplicationConfiguration LoadApplicationConfiguration(WindowsNativeState& nativeState, const std::set<std::string>& customApplicationAssetDirectories)
    {
        const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration = ExampleApp::ApplicationConfig::SdkModel::LoadAppConfig(
            Eegeo::Windows::WindowsFileIO(&nativeState, customApplicationAssetDirectories),
            ExampleApp::ApplicationConfig::SdkModel::WindowsApplicationConfigurationVersionProvider(),
            ExampleApp::ApplicationConfigurationPath);
        return applicationConfiguration;
    }
}

namespace ExampleApp
{
    namespace Windows
    {
        WindowsAppModule::WindowsAppModule(WindowsNativeState& nativeState,
            Eegeo::Rendering::ScreenProperties& screenProperties,
            EGLDisplay& display,
            EGLSurface& shareSurface,
            EGLContext& resourceBuildShareContext,
            bool hasNativeTouchInput,
            int maxDeviceTouchCount)
            : m_nativeState(nativeState)
            , m_screenProperties(screenProperties)
            , m_display(display)
            , m_shareSurface(shareSurface)
            , m_resourceBuildShareContext(resourceBuildShareContext)
            , m_hasNativeTouchInput(hasNativeTouchInput)
            , m_maxDeviceTouchCount(maxDeviceTouchCount)
        {
            m_customApplicationAssetDirectories.insert("SearchResultOnMap");
            m_customApplicationAssetDirectories.insert("ApplicationConfigs");
        }

        void WindowsAppModule::Register(const TContainerBuilder& builder)
        {
            std::set<std::string> customApplicationAssetDirectories;
            customApplicationAssetDirectories.insert("SearchResultOnMap");
            customApplicationAssetDirectories.insert("ApplicationConfigs");

            builder->registerExternallyOwnedInstance(m_nativeState);
            builder->registerExternallyOwnedInstance(m_screenProperties);
            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
            {
                return std::make_shared < ExampleApp::Menu::View::WindowsMenuReactionModel> (false, false);
            }).as<ExampleApp::Menu::View::IMenuReactionModel>().singleInstance();
            builder->registerType<ExampleApp::Metrics::WindowsFlurryMetricsService>().as<ExampleApp::Metrics::IMetricsService>().singleInstance();
            builder->registerType<ExampleApp::InitialExperience::SdkModel::WindowsInitialExperienceModule>().as<ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule>().singleInstance();
            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
            {
                return Hypodermic::makeExternallyOwned(context.resolve<ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule>()->GetInitialExperienceController());
            }).singleInstance();
            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
            {
                auto nativeState = context.resolve<WindowsNativeState>();
                return std::make_shared<Eegeo::UI::NativeAlerts::Windows::WindowsAlertBoxFactory>(nativeState.get());
            }).as<Eegeo::UI::NativeAlerts::IAlertBoxFactory>().singleInstance();

            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
            {
                auto nativeState = context.resolve<WindowsNativeState>();
                auto inputHandler = context.resolve<Eegeo::Windows::Input::IWindowsInputHandler>();
                return std::make_shared<Eegeo::UI::NativeInput::Windows::WindowsKeyboardInputFactory>(nativeState.get(), *inputHandler);
            }).as<Eegeo::UI::NativeInput::IKeyboardInputFactory>().singleInstance();

            builder->registerType<AppInputDelegate>().singleInstance();

            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
            {
                auto nativeState = context.resolve<WindowsNativeState>();
                return std::make_shared<Eegeo::UI::NativeInput::Windows::WindowsInputBoxFactory>(nativeState.get());
            }).as<Eegeo::UI::NativeInput::IInputBoxFactory>().singleInstance();

            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
            {
                auto nativeState = context.resolve<WindowsNativeState>();
                return std::make_shared<Eegeo::UI::NativeAlerts::Windows::WindowsAlertBoxFactory>(nativeState.get());
            }).as<Eegeo::UI::NativeAlerts::IAlertBoxFactory>().singleInstance();
            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
            {
                auto nativeState = context.resolve<WindowsNativeState>();
                Eegeo_ASSERT(nativeState != nullptr);
                return std::make_shared<Eegeo::Windows::WindowsLocationService>(nativeState.get());
            }).as<Eegeo::Location::ILocationService>().singleInstance();

            builder->registerInstanceFactory([this](Hypodermic::ComponentContext& context)
            {
                const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration = LoadApplicationConfiguration(*context.resolve<WindowsNativeState>(), m_customApplicationAssetDirectories);
                return std::make_shared<ExampleApp::ApplicationConfig::ApplicationConfiguration>(applicationConfiguration);
            }).singleInstance();

            builder->registerType<Eegeo::Windows::Input::WindowsInputHandler>().as<Eegeo::Windows::Input::IWindowsInputHandler>().singleInstance();
            builder->registerInstanceFactory([this](Hypodermic::ComponentContext& context)
            {
                auto inputHandler = context.resolve<Eegeo::Windows::Input::IWindowsInputHandler>();
                auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                auto nativeState = context.resolve<WindowsNativeState>();
                auto appConfig = context.resolve<ExampleApp::ApplicationConfig::ApplicationConfiguration>();
                bool enableTouchControls = m_hasNativeTouchInput ? appConfig->IsKioskTouchInputEnabled() : false;
                const Eegeo::Windows::Input::WindowsInputProcessorConfig& windowsInputProcessorConfig = Eegeo::Windows::Input::WindowsInputProcessor::DefaultConfig();
                return std::make_shared<Eegeo::Windows::Input::WindowsInputProcessor>(inputHandler.get(), nativeState->GetWindow(), screenProperties->GetScreenWidth(), screenProperties->GetScreenHeight(), windowsInputProcessorConfig, enableTouchControls, m_maxDeviceTouchCount);
            }).singleInstance();

            builder->registerType<PersistentSettings::WindowsPersistentSettingsModel>().as<PersistentSettings::IPersistentSettingsModel>().singleInstance();
            builder->registerInstanceFactory([this](Hypodermic::ComponentContext& context)
            {
                auto nativeState = context.resolve<WindowsNativeState>();
                auto jpegLoader = context.resolve<Eegeo::Helpers::Jpeg::IJpegLoader>();
                auto appConfig = context.resolve<ExampleApp::ApplicationConfig::ApplicationConfiguration>();
                return std::make_shared<Eegeo::Windows::WindowsPlatformAbstractionModule>(*nativeState,
                    *jpegLoader,
                    m_display,
                    m_resourceBuildShareContext,
                    m_shareSurface,
                    appConfig->EegeoApiKey(),
                    m_customApplicationAssetDirectories);
            }).as<Eegeo::Modules::IPlatformAbstractionModule>().singleInstance();

        }

        void WindowsAppModule::RegisterLeaves()
        {
            RegisterLeaf<WindowsNativeState>();
        }
    }
}
