// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppHost.h"
#include "AndroidSharedGlContext.h"
#include "LatLongAltitude.h"
#include "EegeoWorld.h"
#include "RenderContext.h"
#include "GlobalLighting.h"
#include "GlobalFogging.h"
#include "AppInterface.h"
#include "JpegLoader.h"
#include "EffectHandler.h"
#include "SearchServiceCredentials.h"
#include "AndroidThreadHelper.h"
#include "GlobeCameraController.h"
#include "RenderCamera.h"
#include "CameraHelpers.h"
#include "LoadingScreen.h"
#include "PlatformConfig.h"
#include "AndroidPlatformConfigBuilder.h"
#include "AndroidUrlEncoder.h"
#include "AndroidFileIO.h"
#include "AndroidLocationService.h"
#include "EegeoWorld.h"
#include "EnvironmentFlatteningService.h"
#include "TtyHandler.h"
#include "MenuViewModule.h"
#include "SettingsMenuModule.h"
#include "ModalityModule.h"
#include "ModalBackgroundViewModule.h"
#include "ModalBackgroundNativeView.h"
#include "ModalBackgroundNativeViewModule.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "SearchMenuModule.h"
#include "MenuOptionsModel.h"
#include "SearchModule.h"
#include "SearchResultOnMapModule.h"
#include "WorldPinsModule.h"
#include "RegularTexturePageLayout.h"
#include "PinsModule.h"
#include "SearchResultRepository.h"
#include "LatLongAltitude.h"
#include "SearchResultPoiModule.h"
#include "AndroidPlatformAbstractionModule.h"
#include "FlattenButtonModule.h"
#include "FlattenButtonViewModule.h"
#include "SearchResultPoiViewModule.h"
#include "WorldPinOnMapViewModule.h"
#include "PlaceJumpsModule.h"
#include "IPlaceJumpController.h"
#include "SettingsMenuViewModule.h"
#include "SearchMenuViewModule.h"
#include "CompassViewModule.h"
#include "CompassModule.h"
#include "AboutPageViewModule.h"
#include "AndroidInitialExperienceModule.h"
#include "ViewControllerUpdaterModule.h"
#include "ViewControllerUpdaterModel.h"
#include "TagSearchModule.h"
#include "ScreenProperties.h"
#include "MyPinCreationViewModule.h"
#include "MyPinCreationDetailsViewModule.h"
#include "MyPinDetailsViewModule.h"
#include "InitialExperienceIntroViewModule.h"
#include "Logger.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "SearchResultRepositoryObserver.h"
#include "ApiKey.h"
#include "OptionsViewModule.h"
#include "OptionsView.h"
#include "WatermarkViewModule.h"
#include "WatermarkView.h"
#include "NetworkCapabilities.h"
#include "ApplicationConfigurationModule.h"
#include "IApplicationConfigurationService.h"
#include "SearchVendorNames.h"
#include "UserInteractionEnabledChangedMessage.h"
#include "AndroidApplicationConfigurationVersionProvider.h"
#include "InteriorsExplorerModule.h"
#include "InteriorsExplorerViewModule.h"
#include "SearchResultSectionModule.h"
#include "ConnectivityChangedViewMessage.h"
#include "WebConnectivityValidator.h"
#include "AndroidMenuReactionModel.h"
#include "ApplicationConfigurationModule.h"
#include "ILocationService.h"
#include "AppWiring.h"
#include "MobileExampleApp.h"
#include "AndroidAppModule.h"
#include "IPersistentSettingsModel.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "GlBufferPool.h"
#include "VertexLayoutPool.h"
#include "VertexBindingPool.h"
#include "SearchMenuController.h"
#include "SettingsMenuController.h"
#include "IModalBackgroundView.h"
#include "SettingsMenu.h"
#include "ITagSearchRepository.h"
#include "ISearchMenuView.h"
#include "SearchMenu.h"
#include "InputController.h"

using namespace Eegeo::Android;
using namespace Eegeo::Android::Input;

AppHost::AppHost(
    AndroidNativeState& nativeState,
    Eegeo::Rendering::ScreenProperties screenProperties,
    EGLDisplay display,
    EGLSurface shareSurface,
    EGLContext resourceBuildShareContext
)
    :m_isPaused(false)
    ,m_nativeState(nativeState)
    ,m_registeredUIModules(false)
    ,m_resolvedUIModules(false)
    ,m_uiCreatedMessageReceivedOnNativeThread(false)
	,m_userInteractionEnabledChangedHandler(this, &AppHost::HandleUserInteractionEnabledChanged)
    ,m_loadingScreenCallback(this, &AppHost::OnLoadingScreenComplete)
    ,m_app(nullptr)
    ,m_wiring(nullptr)
    ,m_appInputDelegate(nullptr)
    ,m_connectivityValidator(nullptr)
    ,m_viewControllerUpdater(nullptr)
    ,m_messageBus(nullptr)
    ,m_locationService(nullptr)
    ,m_androidAbstractionModule(nullptr)
    ,m_modalBackground(nullptr)
{
    ASSERT_NATIVE_THREAD

    Eegeo_ASSERT(resourceBuildShareContext != EGL_NO_CONTEXT);

    Eegeo::TtyHandler::TtyEnabled = true;
    Eegeo::AssertHandler::BreakOnAssert = true;

    m_wiring = std::make_shared<ExampleApp::AppWiring>();
    m_wiring->RegisterModuleInstance(std::make_shared<ExampleApp::Android::AndroidAppModule>(nativeState, screenProperties, display, shareSurface, resourceBuildShareContext));
    m_wiring->RegisterDefaultModules();
    m_wiring->RegisterModule<ExampleApp::Watermark::View::WatermarkViewModule>();
    m_wiring->RegisterModule<ExampleApp::WorldPins::View::WorldPinOnMapViewModule>();
    m_wiring->RegisterModule<ExampleApp::FlattenButton::View::FlattenButtonViewModule>();
    m_wiring->RegisterModule<ExampleApp::MyPinCreation::View::MyPinCreationViewModule>();
    m_wiring->RegisterModule<ExampleApp::Compass::View::CompassViewModule>();
    m_wiring->RegisterModule<ExampleApp::ModalBackground::View::ModalBackgroundViewModule>();
    m_wiring->RegisterModule<ExampleApp::ModalBackground::SdkModel::ModalBackgroundNativeViewModule>();
    m_wiring->RegisterModule<ExampleApp::SearchMenu::View::SearchMenuViewModule>();
    m_wiring->RegisterModule<ExampleApp::SettingsMenu::View::SettingsMenuViewModule>();
    m_wiring->RegisterModule<ExampleApp::SearchResultPoi::View::SearchResultPoiViewModule>();
    m_wiring->RegisterModule<ExampleApp::AboutPage::View::AboutPageViewModule>();
    m_wiring->RegisterModule<ExampleApp::Options::View::OptionsViewModule>();
    m_wiring->RegisterModule<ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsViewModule>();
    m_wiring->RegisterModule<ExampleApp::MyPinDetails::View::MyPinDetailsViewModule>();
    m_wiring->RegisterModule<ExampleApp::InitialExperience::View::InitialExperienceIntroViewModule>();
    m_wiring->RegisterModule<ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewModule>();
    m_wiring->RegisterModule<ExampleApp::ViewControllerUpdater::View::ViewControllerUpdaterModule>();
    m_wiring->ApplyModuleRegistrations();
    m_wiring->BuildContainer();
	m_wiring->ResolveLeaf<ExampleApp::ApplicationConfig::ApplicationConfiguration>();
	m_wiring->ResolveLeaf<Eegeo::Modules::IPlatformAbstractionModule>();
	m_wiring->ResolveLeaf<Eegeo::Web::IConnectivityService>();
	m_wiring->ResolveLeaf<ExampleApp::PersistentSettings::IPersistentSettingsModel>();
	m_wiring->ResolveLeaf<ExampleApp::Net::SdkModel::INetworkCapabilities>();
	m_wiring->ResolveLeaf<Eegeo::EegeoWorld>();

	Eegeo::EffectHandler::Initialise();
}

AppHost::~AppHost()
{
    ASSERT_NATIVE_THREAD

    Eegeo::EffectHandler::Reset();
    Eegeo::EffectHandler::Shutdown();

    if (m_app != nullptr)
    {
    	m_app->UnregisterLoadingScreenComplete(m_loadingScreenCallback);
    }
}

void AppHost::OnResume()
{
    ASSERT_NATIVE_THREAD

	if (m_app != nullptr)
	{
		m_app->OnResume();
	}
    m_isPaused = false;
}

void AppHost::OnPause()
{
    ASSERT_NATIVE_THREAD

    m_isPaused = true;
    if (m_app != nullptr)
    {
    	m_app->OnPause();
    }
    if (m_locationService != nullptr)
    {
    	m_locationService->StopListening();
    }
}

void AppHost::NotifyScreenPropertiesChanged(const std::shared_ptr<Eegeo::Rendering::ScreenProperties>& screenProperties)
{
	Eegeo_ASSERT(m_app != nullptr);
	if (m_app != nullptr)
	{
		m_app->NotifyScreenPropertiesChanged(screenProperties);
	}
}

void AppHost::SetSharedSurface(EGLSurface sharedSurface)
{
    ASSERT_NATIVE_THREAD

	if (m_androidAbstractionModule != nullptr)
	{
		m_androidAbstractionModule->UpdateSurface(sharedSurface);
	}
}

void AppHost::SetViewportOffset(float x, float y)
{
    ASSERT_NATIVE_THREAD

	m_appInputDelegate->SetViewportOffset(x, y);
}

void AppHost::HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event)
{
	ASSERT_NATIVE_THREAD
	m_appInputDelegate->HandleTouchInputEvent(event);
}

void AppHost::Update(float dt)
{
    ASSERT_NATIVE_THREAD

    if(m_isPaused || m_app == nullptr)
    {
        return;
    }

    GetMessageBus().FlushToNative();

    m_app->Update(dt);

    m_modalBackground->Update(dt);
}

void AppHost::OnLoadingScreenComplete()
{
	DispatchRevealUiMessageToUiThreadFromNativeThread();
}

void AppHost::Draw(float dt)
{
    ASSERT_NATIVE_THREAD

    if(m_isPaused || m_app == nullptr)
    {
        return;
    }

    m_app->Draw(dt);

    m_appInputDelegate->Update(dt);
}

void AppHost::HandleApplicationUiCreatedOnNativeThread()
{
    ASSERT_NATIVE_THREAD
	m_wiring->ResolveNativeLeaves();
	m_wiring->ResolveModules();
	m_app = m_wiring->BuildMobileExampleApp();
	m_app->RegisterLoadingScreenComplete(m_loadingScreenCallback);
	m_appInputDelegate = m_wiring->Resolve<AppInputDelegate>();

	m_connectivityValidator = m_wiring->Resolve<Eegeo::Web::WebConnectivityValidator>();
	m_viewControllerUpdater = m_wiring->Resolve<ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModel>();
	m_messageBus = m_wiring->Resolve<ExampleApp::ExampleAppMessaging::TMessageBus>();
	m_locationService = m_wiring->Resolve<Eegeo::Location::ILocationService>();
	m_androidAbstractionModule = std::dynamic_pointer_cast<Eegeo::Android::AndroidPlatformAbstractionModule>(m_wiring->Resolve<Eegeo::Modules::IPlatformAbstractionModule>());
	m_modalBackground = m_wiring->Resolve<ExampleApp::ModalBackground::SdkModel::ModalBackgroundNativeView>();

	GetMessageBus().SubscribeUi(m_userInteractionEnabledChangedHandler);
	m_uiCreatedMessageReceivedOnNativeThread = true;
	PublishNetworkConnectivityStateToUIThread();
}

void AppHost::PublishNetworkConnectivityStateToUIThread()
{
    // Network validation runs before UI is constructed and so it is not notified and assumed there is no connection: MPLY-6584
    // The state should be passed on opening the UI view, but currently this is done from the UI thread. Pin Creation UI probably needs a refactor.

    ASSERT_NATIVE_THREAD
    
    GetMessageBus().Publish(ExampleApp::Net::ConnectivityChangedViewMessage(m_connectivityValidator->IsValid()));
}

void AppHost::DispatchRevealUiMessageToUiThreadFromNativeThread()
{
    ASSERT_NATIVE_THREAD

    AndroidSafeNativeThreadAttachment attached(m_nativeState);
    JNIEnv* env = attached.envForThread;
    jmethodID dispatchRevealUiMessageToUiThreadFromNativeThread = env->GetMethodID(m_nativeState.activityClass, "dispatchRevealUiMessageToUiThreadFromNativeThread", "(J)V");
    env->CallVoidMethod(m_nativeState.activity, dispatchRevealUiMessageToUiThreadFromNativeThread, (jlong)(this));
}

void AppHost::DispatchUiCreatedMessageToNativeThreadFromUiThread()
{
    ASSERT_UI_THREAD

    AndroidSafeNativeThreadAttachment attached(m_nativeState);
    JNIEnv* env = attached.envForThread;
    jmethodID dispatchUiCreatedMessageToNativeThreadFromUiThread = env->GetMethodID(m_nativeState.activityClass, "dispatchUiCreatedMessageToNativeThreadFromUiThread", "(J)V");
    env->CallVoidMethod(m_nativeState.activity, dispatchUiCreatedMessageToNativeThreadFromUiThread, (jlong)(this));
}

void AppHost::RevealUiFromUiThread()
{
    ASSERT_UI_THREAD

    m_app->InitialiseApplicationViewState(m_wiring->GetContainer());
}

void AppHost::CreateUiFromUiThread()
{
    ASSERT_UI_THREAD

    Eegeo_ASSERT(!m_registeredUIModules);
    CreateApplicationViewModulesFromUiThread();
    DispatchUiCreatedMessageToNativeThreadFromUiThread();
}

void AppHost::UpdateUiViewsFromUiThread(float dt)
{
    ASSERT_UI_THREAD

	if (m_app != nullptr)
	{
		GetMessageBus().FlushToUi();
	}

    if(!m_resolvedUIModules)
    {
        CreateUiFromUiThread();
    }
    else if (m_uiCreatedMessageReceivedOnNativeThread)
    {
    	m_viewControllerUpdater->UpdateObjectsUiThread(dt);
    }
}

void AppHost::DestroyUiFromUiThread()
{
    ASSERT_UI_THREAD

    DestroyApplicationViewModulesFromUiThread();
}

void AppHost::CreateApplicationViewModulesFromUiThread()
{
    ASSERT_UI_THREAD
    m_wiring->ResolveUiLeaves();
    AddViewControllerUpdatable<ExampleApp::SettingsMenu::View::SettingsMenuController>();
    AddViewControllerUpdatable<ExampleApp::SearchMenu::View::SearchMenuController>();
	m_resolvedUIModules = true;
    SetTouchExclusivity();
}

void AppHost::DestroyApplicationViewModulesFromUiThread()
{
    ASSERT_UI_THREAD

    if(m_resolvedUIModules)
    {
    	GetMessageBus().UnsubscribeUi(m_userInteractionEnabledChangedHandler);
    }
    m_resolvedUIModules = false;
    m_registeredUIModules = false;
}

void AppHost::SetTouchExclusivity()
{
	ASSERT_UI_THREAD

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	const std::string methodName = "setTouchExclusivity";
	jmethodID setTouchExclusivityMethod = env->GetMethodID(m_nativeState.activityClass, methodName.c_str(), "()V");
	env->CallVoidMethod(m_nativeState.activity, setTouchExclusivityMethod);
}


void AppHost::HandleUserInteractionEnabledChanged(const ExampleApp::UserInteraction::UserInteractionEnabledChangedMessage& message)
{
	ASSERT_UI_THREAD

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	const std::string methodName = "setTouchEnabled";
	jmethodID touchEnabledMethod = env->GetMethodID(m_nativeState.activityClass, methodName.c_str(), "(Z)V");
	env->CallVoidMethod(m_nativeState.activity, touchEnabledMethod, message.IsEnabled());
}

ExampleApp::ExampleAppMessaging::TMessageBus& AppHost::GetMessageBus()
{
	Eegeo_ASSERT(m_resolvedUIModules);
    return *m_messageBus;
}

