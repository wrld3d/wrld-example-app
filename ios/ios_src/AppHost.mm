// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "IJpegLoader.h"
#include "ILocationService.h"
#include "IConnectivityService.h"
#include "IPlatformAbstractionModule.h"
#include "IPersistentSettingsModel.h"
#include "IMetricsService.h"

#include "App.h"
#include "MenuController.h"
#include "AppHost.h"
#include "LatLongAltitude.h"
#include "EegeoWorld.h"
#include "ScreenProperties.h"
#include "AppInterface.h"
#include "EffectHandler.h"
#include "SearchServiceCredentials.h"
#include "GlobeCameraController.h"
#include "RenderCamera.h"
#include "CameraHelpers.h"
#include "LoadingScreen.h"
#include "PlatformConfig.h"
#include "iOSPlatformConfigBuilder.h"
#include "EegeoWorld.h"
#include "JpegLoader.h"
#include "iOSPlatformAbstractionModule.h"
#include "ViewController.h"
#include "SettingsMenuViewModule.h"
#include "SettingsMenuView.h"
#include "SearchMenuViewModule.h"
#include "SearchMenuView.h"
#include "ModalBackgroundView.h"
#include "FlattenButtonView.h"
#include "FlattenButtonViewModule.h"
#include "WorldPinOnMapViewModule.h"
#include "WorldPinOnMapViewContainer.h"
#include "SearchResultPoiViewModule.h"
#include "SearchResultPoiView.h"
#include "SearchResultSectionModule.h"
#include "CompassViewModule.h"
#include "CompassView.h"
#include "CompassModel.h"
#include "ViewControllerUpdaterModule.h"
#include "IViewControllerUpdaterModel.h"
#include "iOSInitialExperienceModule.h"
#include "AboutPageViewModule.h"
#include "AboutPageView.h"
#include "TagSearchModule.h"
#include "MyPinCreationInitiationViewModule.h"
#include "MyPinCreationInitiationView.h"
#include "MyPinCreationConfirmationViewModule.h"
#include "MyPinCreationConfirmationView.h"
#include "MyPinCreationDetailsViewModule.h"
#include "MyPinCreationDetailsView.h"
#include "MyPinDetailsViewModule.h"
#include "MyPinDetailsView.h"
#include "ApiKey.h"
#include "ModalBackgroundViewModule.h"
#include "OptionsViewModule.h"
#include "OptionsView.h"
#include "WatermarkViewModule.h"
#include "WatermarkView.h"
#include "TourWebViewModule.h"
#include "TourExplorerViewModule.h"
#include "TourExplorerView.h"
#include "NetworkCapabilities.h"
#include "InitialExperienceIntroViewModule.h"
#include "InitialExperienceIntroView.h"
#include "InitialExperienceIntroBackgroundView.h"
#include "ApplicationConfigurationModule.h"
#include "IApplicationConfigurationService.h"
#include "InteriorsExplorerViewModule.h"
#include "InteriorsPresentationModule.h"
#include "InteriorsExplorerView.h"
#include "TourHovercardView.h"
#include "TourFullScreenImageViewModule.h"
#include "TourFullScreenImageViewModel.h"
#include "TourFullScreenImageView.h"
#include "ImageStore.h"
#include "SearchVendorNames.h"
#include "UserInteractionEnabledChangedMessage.h"
#include "SurveyViewModule.h"
#include "IOSMenuReactionModel.h"
#include "Module.h"
#include "MobileExampleApp.h"
#include "IWatermarkViewModel.h"
#include "SettingsMenuController.h"
#include "IModalBackgroundView.h"
#include "SearchResultPoiViewContainer.h"
#include "IInitialExperienceController.h"
#include "SearchMenuController.h"
#include "ISearchMenuView.h"
#include "ITagSearchRepository.h"
#include "IWorldAreaLoaderModel.h"

#include "iOSAbstractionIoCModule.h"
#include "iOSAppModule.h"
#include <memory>
#include "ViewWrap.h"

#import "UIView+TouchExclusivity.h"

using namespace Eegeo::iOS;

AppHost::AppHost(
    ViewController& viewController,
    UIView* pView,
    Eegeo::Rendering::ScreenProperties screenProperties,
    ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
    ExampleApp::Metrics::iOSFlurryMetricsService& metricsService
)

    :m_pView(pView)
    ,m_viewController(viewController)
    ,m_pTourWebViewModule(NULL)
    ,m_pTourFullScreenImageViewModule(NULL)
    ,m_pTourExplorerViewModule(NULL)
    ,m_userInteractionEnabledChangedHandler(this, &AppHost::HandleUserInteractionEnabledChanged)
    ,m_loadingSreenCompleteCallback(this, &AppHost::OnLoadingScreenComplete)
{
    Eegeo::TtyHandler::TtyEnabled = true;
    
    m_wiring = std::make_shared<ExampleApp::AppWiring>();
    m_wiring->RegisterModule<ExampleApp::iOS::iOSAbstractionIoCModule>();
    m_wiring->RegisterModuleInstance(std::make_shared<ExampleApp::iOS::iOSAppModule>(screenProperties, applicationConfiguration, metricsService, m_viewController));
    m_wiring->RegisterDefaultModules();
    RegisterApplicationViewModules();
    m_wiring->ResolveModules();
    
    m_app = m_wiring->BuildMobileExampleApp();
    m_app->RegisterLoadingScreenComplete(m_loadingSreenCompleteCallback);
   
    m_pAppInputDelegate = Eegeo_NEW(AppInputDelegate)(*m_wiring->Resolve<ExampleApp::IInputController>(), m_viewController, screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight(), screenProperties.GetPixelScale());

    Eegeo::EffectHandler::Initialise();
    GetMessageBus().SubscribeUi(m_userInteractionEnabledChangedHandler);
    AddApplicationViews();
}

ExampleApp::ExampleAppMessaging::TMessageBus& AppHost::GetMessageBus()
{
    return *(m_wiring->Resolve<ExampleApp::ExampleAppMessaging::TMessageBus>());
}

ExampleApp::ExampleAppMessaging::TSdkModelDomainEventBus& AppHost::GetSdkMessageBus()
{
    return *(m_wiring->Resolve<ExampleApp::ExampleAppMessaging::TSdkModelDomainEventBus>());
}

AppHost::~AppHost()
{
    m_app->UnregisterLoadingScreenComplete(m_loadingSreenCompleteCallback);

    GetMessageBus().UnsubscribeUi(m_userInteractionEnabledChangedHandler);
    
    Eegeo_DELETE m_pAppInputDelegate;
    m_pAppInputDelegate = NULL;

    DestroyApplicationViewModules();

    Eegeo::EffectHandler::Reset();
    Eegeo::EffectHandler::Shutdown();
}

void AppHost::OnLoadingScreenComplete()
{
    m_app->InitialiseApplicationViewState(m_wiring->GetContainer());
}

void AppHost::OnResume()
{
    m_wiring->Resolve<ExampleApp::LinkOutObserver::LinkOutObserver>()->OnAppResume();
    
    m_app->OnResume();
}

void AppHost::OnPause()
{
    m_app->OnPause();
}

void AppHost::NotifyScreenPropertiesChanged(const std::shared_ptr<Eegeo::Rendering::ScreenProperties>& screenProperties)
{
    m_app->NotifyScreenPropertiesChanged(screenProperties);
}

void AppHost::Update(float dt)
{
    if (!m_wiring->Resolve<AppLocationDelegate>()->HasReceivedPermissionResponse())
    {
        return;
    }

    m_app->Update(dt);
    m_wiring->Resolve<ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModel>()->UpdateObjectsUiThread(dt);

    GetMessageBus().FlushToUi();
    GetMessageBus().FlushToNative();
}

void AppHost::Draw(float dt)
{
    m_app->Draw(dt);
}

bool AppHost::IsRunning()
{
    return m_app->IsRunning();
}

void AppHost::AddApplicationViews()
{
    AddSubview<WorldPinOnMapViewContainerWrapper>();
    AddSubview<InitialExperienceIntroBackgroundViewWrapper>();
    
    AddSubview<WatermarkViewWrapper>();
    AddSubview<ModalBackgroundViewWrapper>();
    AddSubview<SettingsMenuViewWrapper>();
    AddSubview<SearchResultPoiViewContainerWrapper>();
    AddSubview<FlattenButtonViewWrapper>();
    AddSubview<CompassViewWrapper>();
    AddSubview<InitialExperienceIntroViewWrapper>();
    AddSubview<OptionsViewWrapper>();

    AddSubview<AboutPageViewWrapper>();
    AddSubview<MyPinCreationInitiationViewWrapper>();
    AddSubview<MyPinCreationConfirmationViewWrapper>();
    AddSubview<MyPinCreationDetailsViewWrapper>();
    AddSubview<MyPinDetailsViewWrapper>();
    
    AddSubview<SearchMenuViewWrapper>();
    AddSubview<InteriorsExplorerViewWrapper>();
    AddSubview<InteriorsExplorerTutorialViewWrapper>();
    
    AddViewControllerUpdatable<ExampleApp::SettingsMenu::View::SettingsMenuController>();
    AddViewControllerUpdatable<ExampleApp::SearchMenu::View::SearchMenuController>();
}

void AppHost::RegisterApplicationViewModules()
{
    m_wiring->RegisterModule<ExampleApp::Watermark::View::WatermarkViewModule>();
    m_wiring->RegisterModule<ExampleApp::ModalBackground::View::ModalBackgroundViewModule>();
    m_wiring->RegisterModule<ExampleApp::SettingsMenu::View::SettingsMenuViewModule>();
    m_wiring->RegisterModule<ExampleApp::SearchResultPoi::View::SearchResultPoiViewModule>();
    m_wiring->RegisterModule<ExampleApp::FlattenButton::View::FlattenButtonViewModule>();
    m_wiring->RegisterModule<ExampleApp::WorldPins::View::WorldPinOnMapViewModule>();
    m_wiring->RegisterModule<ExampleApp::Compass::View::CompassViewModule>();
    m_wiring->RegisterModule<ExampleApp::InitialExperience::View::InitialExperienceIntroViewModule>();
    m_wiring->RegisterModule<ExampleApp::AboutPage::View::AboutPageViewModule>();
    m_wiring->RegisterModule<ExampleApp::Options::View::OptionsViewModule>();
    m_wiring->RegisterModule<ExampleApp::MyPinCreation::View::MyPinCreationInitiationViewModule>();
    m_wiring->RegisterModule<ExampleApp::MyPinCreation::View::MyPinCreationConfirmationViewModule>();
    m_wiring->RegisterModule<ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsViewModule>();
    m_wiring->RegisterModule<ExampleApp::MyPinDetails::View::MyPinDetailsViewModule>();
    m_wiring->RegisterModule<ExampleApp::SearchMenu::View::SearchMenuViewModule>();
    m_wiring->RegisterModule<ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewModule>();
}

void AppHost::DestroyApplicationViewModules()
{
    Eegeo_DELETE m_pSurveyViewModule;
    
    Eegeo_DELETE m_pTourFullScreenImageViewModule;
    
    Eegeo_DELETE m_pTourExplorerViewModule;
    
    Eegeo_DELETE m_pTourWebViewModule;
}

void AppHost::SetTouchExclusivity()
{
    [m_pView setTouchExclusivity:m_pView];
}

void AppHost::HandleUserInteractionEnabledChanged(const ExampleApp::UserInteraction::UserInteractionEnabledChangedMessage& message)
{
    m_pView.userInteractionEnabled = message.IsEnabled();
}

