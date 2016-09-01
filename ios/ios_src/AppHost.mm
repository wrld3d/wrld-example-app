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
#include "SearchResultSectionViewModule.h"
#include "CompassViewModule.h"
#include "CompassView.h"
#include "CompassModel.h"
#include "ViewControllerUpdaterModule.h"
#include "IViewControllerUpdaterModel.h"
#include "iOSInitialExperienceModule.h"
#include "AboutPageViewModule.h"
#include "AboutPageView.h"
#include "CategorySearchModule.h"
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

#include "IWatermarkViewModel.h"

#include <memory>

#import "UIView+TouchExclusivity.h"

using namespace Eegeo::iOS;

class iOSAbstractionIoCModule : public ExampleApp::Module
{
public:
    void Register(const ExampleApp::TContainerBuilder& builder)
    {
        builder->registerType<Eegeo::UI::NativeInput::iOS::iOSInputBoxFactory>().as<Eegeo::UI::NativeInput::IInputBoxFactory>().singleInstance();
        builder->registerType<Eegeo::UI::NativeInput::iOS::iOSKeyboardInputFactory>().as<Eegeo::UI::NativeInput::IKeyboardInputFactory>().singleInstance();
        builder->registerType<Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory>().as<Eegeo::UI::NativeAlerts::IAlertBoxFactory>().singleInstance();
        
        builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
        {
            return std::make_shared<Eegeo::UI::NativeUIFactories>(*(context.resolve<Eegeo::UI::NativeAlerts::IAlertBoxFactory>()),
                                                                  *(context.resolve<Eegeo::UI::NativeInput::IInputBoxFactory>()),
                                                                  *(context.resolve<Eegeo::UI::NativeInput::IKeyboardInputFactory>()));
        }).singleInstance();
        
        builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
        {
            auto appConfig = context.resolve<ExampleApp::ApplicationConfig::ApplicationConfiguration>();
            return std::make_shared<Eegeo::iOS::iOSPlatformAbstractionModule>(*(context.resolve<Eegeo::Helpers::Jpeg::IJpegLoader>()), appConfig->EegeoApiKey());
        }).as<Eegeo::Modules::IPlatformAbstractionModule>().singleInstance();
        
        // TODO, template out?
        
        builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
        {
            return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::Modules::IPlatformAbstractionModule>()->GetTextureFileLoader());
        }).singleInstance();
        
        builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
        {
            return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::Modules::IPlatformAbstractionModule>()->GetHttpCache());
        }).singleInstance();
    }
};

class iOSAppModule : public ExampleApp::Module
{
public:
    iOSAppModule(
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
    
    void Register(const ExampleApp::TContainerBuilder& builder)
    {
        builder->registerExternallyOwnedInstance(m_metricsService).as<ExampleApp::Metrics::IMetricsService>();
        builder->registerExternallyOwnedInstance(m_screenProperties);
        builder->registerExternallyOwnedInstance(m_applicationConfiguration);
        builder->registerType<iOSLocationService>().as<Eegeo::Location::ILocationService>().singleInstance();
        builder->registerType<iOSConnectivityService>().as<Eegeo::Web::IConnectivityService>().singleInstance();
        builder->registerType<ExampleApp::PersistentSettings::iOSPersistentSettingsModel>().as<ExampleApp::PersistentSettings::IPersistentSettingsModel>().singleInstance();
        builder->registerType<ExampleApp::InitialExperience::iOSInitialExperienceModule>().as<ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule>().singleInstance();
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                         {
                                             return Hypodermic::makeExternallyOwned(context.resolve<ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule>()->GetInitialExperienceModel());
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
                                                        return std::make_shared<AppLocationDelegate>(context.resolve<iOSLocationService>(), m_viewController);
                                                    }).singleInstance();
    }
private:
    Eegeo::Rendering::ScreenProperties m_screenProperties;
    ExampleApp::ApplicationConfig::ApplicationConfiguration& m_applicationConfiguration;
    ExampleApp::Metrics::iOSFlurryMetricsService& m_metricsService;
    ViewController& m_viewController;
};

AppHost::AppHost(
    ViewController& viewController,
    UIView* pView,
    Eegeo::Rendering::ScreenProperties screenProperties,
    ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
    ExampleApp::Metrics::iOSFlurryMetricsService& metricsService
)

    :m_pView(pView)
    ,m_viewController(viewController)
    ,m_failAlertHandler(this, &AppHost::HandleStartupFailure)
    ,m_pTourWebViewModule(NULL)
    ,m_pTourFullScreenImageViewModule(NULL)
    ,m_pTourExplorerViewModule(NULL)
    ,m_userInteractionEnabledChangedHandler(this, &AppHost::HandleUserInteractionEnabledChanged)
    ,m_loadingSreenCompleteCallback(this, &AppHost::OnLoadingScreenComplete)
{
    Eegeo::TtyHandler::TtyEnabled = true;
    
    m_wiring = std::make_shared<ExampleApp::AppWiring>();
    m_wiring->RegisterModule<iOSAbstractionIoCModule>();
    m_wiring->RegisterModuleInstance(std::make_shared<iOSAppModule>(screenProperties, applicationConfiguration, metricsService, m_viewController));
    m_wiring->RegisterDefaultModules();
    RegisterApplicationViewModules();
    m_wiring->ResolveModules();

    m_pImageStore = [[ImageStore alloc]init];
    
//    m_containerBuilder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
//                                                {
//                                                    return std::shared_ptr<AppHost::AppHost>(this); // Danger: shared from this, enable_shared_from_this, or better extract out a sane error handler..
//                                                }).as<Eegeo::IEegeoErrorHandler>().singleInstance();
    
    
    // TODO : More to put in the container past here...
    
//    m_container->resolve<ExampleApp::LinkOutObserver::LinkOutObserver>()->OnAppStart();
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
    
    [m_pImageStore release];
    m_pImageStore = nil;

    Eegeo::EffectHandler::Reset();
    Eegeo::EffectHandler::Shutdown();
}

void AppHost::OnLoadingScreenComplete()
{
    // temporary, move to another cross-platform type.
    m_wiring->Resolve<ExampleApp::Watermark::View::IWatermarkViewModel>()->AddToScreen();
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

    /*if(m_pApp->IsLoadingScreenComplete() && !m_requestedApplicationInitialiseViewState)
    {
        m_requestedApplicationInitialiseViewState = true;
        m_pApp->InitialiseApplicationViewState();
    }*/

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
    auto watermarkView = m_wiring->Resolve<WatermarkViewWrapper>()->Get();
    [m_pView addSubview: watermarkView];
}

void AppHost::RegisterApplicationViewModules()
{
    m_wiring->RegisterModule<ExampleApp::Watermark::View::WatermarkViewModule>();
    /*m_pWatermarkViewModule = Eegeo_NEW(ExampleApp::Watermark::View::WatermarkViewModule)(app.WatermarkModule().GetWatermarkViewModel(),
                                                                                         app.WatermarkModule().GetWatermarkDataRepository(),
                                                                                         screenProperties,
                                                                                         GetMessageBus(),
                                                                                         *(m_container->resolve<ExampleApp::Metrics::IMetricsService>()));

    m_pModalBackgroundViewModule = Eegeo_NEW(ExampleApp::ModalBackground::View::ModalBackgroundViewModule)(app.ModalityModule().GetModalityModel(), screenProperties);
    
    m_pSettingsMenuViewModule = Eegeo_NEW(ExampleApp::SettingsMenu::View::SettingsMenuViewModule)(app.SettingsMenuModule().GetSettingsMenuModel(),
                                                                                                  app.SettingsMenuModule().GetSettingsMenuViewModel(),
                                                                                                  screenProperties,
                                                                                                  m_pModalBackgroundViewModule->GetModalBackgroundViewInterop(),
                                                                                                  GetMessageBus());
    
    m_pSearchMenuViewModule = Eegeo_NEW(ExampleApp::SearchMenu::View::SearchMenuViewModule)(app.SearchMenuModule().GetSearchMenuModel(),
                                                                                            app.SearchMenuModule().GetSearchMenuViewModel(),
                                                                                            app.SearchMenuModule().GetSearchSectionViewModel(),
                                                                                            screenProperties,
                                                                                            app.CategorySearchModule().GetCategorySearchRepository(),
                                                                                            m_pModalBackgroundViewModule->GetModalBackgroundViewInterop(),
                                                                                            GetMessageBus());
    
    m_pSearchResultSectionViewModule = Eegeo_NEW(ExampleApp::SearchResultSection::View::SearchResultSectionViewModule)(app.SearchMenuModule().GetSearchMenuViewModel(),
                                                                                                                       app.SearchResultSectionModule().GetSearchResultSectionOptionsModel(),
                                                                                                                       app.SearchResultSectionModule().GetSearchResultSectionOrder(),
                                                                                                                       GetMessageBus(),
                                                                                                                       *(m_container->resolve<ExampleApp::Menu::View::IMenuReactionModel>()),
                                                                                                                       app.SearchResultPoiModule().GetSearchResultPoiViewModel());

    m_pSearchResultPoiViewModule = Eegeo_NEW(ExampleApp::SearchResultPoi::View::SearchResultPoiViewModule)(app.SearchResultPoiModule().GetSearchResultPoiViewModel(),
                                                                                                           GetMessageBus(),
                                                                                                           *(m_container->resolve<ExampleApp::Metrics::IMetricsService>()));

    m_pFlattenButtonViewModule = Eegeo_NEW(ExampleApp::FlattenButton::View::FlattenButtonViewModule)(
                                     app.FlattenButtonModule().GetFlattenButtonViewModel(),
                                     screenProperties,
                                     GetMessageBus(),
                                     *(m_container->resolve<ExampleApp::Metrics::IMetricsService>()));

    m_pWorldPinOnMapViewModule = Eegeo_NEW(ExampleApp::WorldPins::View::WorldPinOnMapViewModule)(app.WorldPinsModule().GetWorldPinInFocusViewModel(),
                                 app.WorldPinsModule().GetScreenControlViewModel(),
                                 app.ModalityModule().GetModalityModel(),
                                 app.PinDiameter(),
                                 screenProperties.GetPixelScale(),
                                 m_pImageStore);
    
    m_pCompassViewModule = Eegeo_NEW(ExampleApp::Compass::View::CompassViewModule)(app.CompassModule().GetCompassViewModel(),
                           screenProperties,
                           GetMessageBus());

    m_pAboutPageViewModule = Eegeo_NEW(ExampleApp::AboutPage::View::AboutPageViewModule)(app.AboutPageModule().GetAboutPageViewModel(), *(m_container->resolve<ExampleApp::Metrics::IMetricsService>()));
    
    m_pOptionsViewModule = Eegeo_NEW(ExampleApp::Options::View::OptionsViewModule)(app.OptionsModule().GetOptionsViewModel(),
                                                                                   *(m_container->resolve<Eegeo::Helpers::IHttpCache>()),
                                                                                   GetMessageBus(),
                                                                                   app.World().GetWorkPool());

    m_pMyPinCreationInitiationViewModule = Eegeo_NEW(ExampleApp::MyPinCreation::View::MyPinCreationInitiationViewModule)(GetMessageBus(),
                                           app.MyPinCreationModule().GetMyPinCreationInitiationViewModel(),
                                           app.MyPinCreationModule().GetMyPinCreationConfirmationViewModel(),
                                           screenProperties,
                                           *(m_container->resolve<ExampleApp::Metrics::IMetricsService>()));

    m_pMyPinCreationConfirmationViewModule = Eegeo_NEW(ExampleApp::MyPinCreation::View::MyPinCreationConfirmationViewModule)(GetMessageBus(),
            app.MyPinCreationModule().GetMyPinCreationConfirmationViewModel(),
            app.MyPinCreationModule().GetMyPinCreationCompositeViewModel(),
            app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
            screenProperties,
            *(m_container->resolve<ExampleApp::Metrics::IMetricsService>()));

    m_pMyPinCreationDetailsViewModule = Eegeo_NEW(ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsViewModule)(
                                            GetMessageBus(),
                                            app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
                                            screenProperties,
                                            *(m_container->resolve<ExampleApp::Metrics::IMetricsService>()),
                                            &m_viewController);

    m_pMyPinDetailsViewModule = Eegeo_NEW(ExampleApp::MyPinDetails::View::MyPinDetailsViewModule)(GetMessageBus(),
                                app.MyPinDetailsModule().GetMyPinDetailsViewModel(),
                                screenProperties);
    
    
    if(app.ToursEnabled())
    {
        m_pTourWebViewModule = Eegeo_NEW(ExampleApp::Tours::View::TourWeb::TourWebViewModule)(screenProperties);
        
        m_pTourExplorerViewModule = Eegeo_NEW(ExampleApp::Tours::View::TourExplorer::TourExplorerViewModule)
                                                                                           (GetMessageBus(),
                                                                                            app.ToursModule().GetToursExplorerViewModel(),
                                                                                            *(m_container->resolve<ExampleApp::URLRequest::View::URLRequestHandler>()),
                                                                                            app.ToursModule().GetToursExplorerCompositeViewController(),
                                                                                            screenProperties,
                                                                                            m_pImageStore);
    
        m_pTourFullScreenImageViewModule = Eegeo_NEW(ExampleApp::Tours::View::TourFullScreenImage::TourFullScreenImageViewModule)(app.ToursModule().GetTourFullScreenImageViewModel(),
                                                                                                                                  screenProperties);
    }
    
    m_pInitialExperienceIntroViewModule = Eegeo_NEW(ExampleApp::InitialExperience::View::InitialExperienceIntroViewModule)(GetMessageBus());
    
    
    m_pInteriorsExplorerViewModule = Eegeo_NEW(ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewModule)(app.InteriorsExplorerModule().GetInteriorsExplorerViewModel(),
                                                                                                                 GetMessageBus(),
                                                                                                                 screenProperties,
                                                                                                                 app.GetIdentityProvider());
    
    m_pSurveyViewModule = Eegeo_NEW(ExampleApp::Surveys::View::SurveyViewModule)(GetMessageBus(),
                                                                                 *(m_container->resolve<ExampleApp::Metrics::IMetricsService>()),
                                                                                 *(m_container->resolve<ExampleApp::URLRequest::View::URLRequestHandler>()));
    
    // 3d map view layer.
    [m_pView addSubview: &m_pWorldPinOnMapViewModule->GetWorldPinOnMapView()];
    
    // Initial Experience background
    [m_pView addSubview: &m_pInitialExperienceIntroViewModule->GetIntroBackgroundView()];

    // HUD behind modal background layer.
    [m_pView addSubview: &m_pWatermarkViewModule->GetWatermarkView()];
    [m_pView addSubview: &m_pFlattenButtonViewModule->GetFlattenButtonView()];
    [m_pView addSubview: &m_pCompassViewModule->GetCompassView()];
    [m_pView addSubview: &m_pMyPinCreationInitiationViewModule->GetMyPinCreationInitiationView()];
    [m_pView addSubview: &m_pMyPinCreationConfirmationViewModule->GetMyPinCreationConfirmationView()];
    if(m_pApp->ToursEnabled())
    {
        [m_pView addSubview: &m_pTourFullScreenImageViewModule->GetTourFullScreenImageView()];
        [m_pView addSubview: &m_pTourExplorerViewModule->GetTourExplorerView()];
    }
    [m_pView addSubview: &m_pInteriorsExplorerViewModule->GetView()];

    // Modal background layer.
    [m_pView addSubview: &m_pModalBackgroundViewModule->GetModalBackgroundView()];

    // Menus & HUD layer.
    [m_pView addSubview: &m_pSettingsMenuViewModule->GetSettingsMenuView()];
    [m_pView addSubview: &m_pSearchMenuViewModule->GetSearchMenuView()];

    // Pop-up layer.
    [m_pView addSubview: &m_pSearchResultPoiViewModule->GetView()];
    [m_pView addSubview: &m_pAboutPageViewModule->GetAboutPageView()];
    [m_pView addSubview: &m_pOptionsViewModule->GetOptionsView()];
    [m_pView addSubview: &m_pMyPinCreationDetailsViewModule->GetMyPinCreationDetailsView()];
    [m_pView addSubview: &m_pMyPinDetailsViewModule->GetMyPinDetailsView()];
    if(m_pApp->ToursEnabled())
    {
        [m_pView addSubview: &m_pTourWebViewModule->GetTourWebView()];
    }
    
    // Initial experience layer
    [m_pView addSubview: &m_pInitialExperienceIntroViewModule->GetIntroView()];

    m_pViewControllerUpdaterModule = Eegeo_NEW(ExampleApp::ViewControllerUpdater::View::ViewControllerUpdaterModule);
    ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModel& viewControllerUpdaterModel = m_pViewControllerUpdaterModule->GetViewControllerUpdaterModel();
    
    viewControllerUpdaterModel.AddUpdateableObject(m_pSettingsMenuViewModule->GetMenuController());
    viewControllerUpdaterModel.AddUpdateableObject(m_pSearchMenuViewModule->GetMenuController());
    
    SetTouchExclusivity(); */
}

void AppHost::DestroyApplicationViewModules()
{
    // 3d map view layer.
    [&m_pWorldPinOnMapViewModule->GetWorldPinOnMapView() removeFromSuperview];
    
    [&m_pInitialExperienceIntroViewModule->GetIntroBackgroundView() removeFromSuperview];

    // HUD behind modal background layer.
    //[&m_pWatermarkViewModule->GetWatermarkView() removeFromSuperview];
    [&m_pFlattenButtonViewModule->GetFlattenButtonView() removeFromSuperview];
    [&m_pCompassViewModule->GetCompassView() removeFromSuperview];
    [&m_pMyPinCreationInitiationViewModule->GetMyPinCreationInitiationView() removeFromSuperview];
    [&m_pMyPinCreationConfirmationViewModule->GetMyPinCreationConfirmationView() removeFromSuperview];
    /*if(m_pApp->ToursEnabled())
    {
        [&m_pTourFullScreenImageViewModule->GetTourFullScreenImageView() removeFromSuperview];
        [&m_pTourExplorerViewModule->GetTourExplorerView() removeFromSuperview];
    }*/
    [&m_pInteriorsExplorerViewModule->GetView() removeFromSuperview];

    // Modal background layer.
    [&m_pModalBackgroundViewModule->GetModalBackgroundView() removeFromSuperview];

    // Menus & HUD layer.
    [&m_pSettingsMenuViewModule->GetSettingsMenuView() removeFromSuperview];
    [&m_pSearchMenuViewModule->GetSearchMenuView() removeFromSuperview];

    // Pop-up layer.
    [&m_pMyPinDetailsViewModule->GetMyPinDetailsView() removeFromSuperview];
    [&m_pMyPinCreationDetailsViewModule->GetMyPinCreationDetailsView() removeFromSuperview];
    [&m_pSearchResultPoiViewModule->GetView() removeFromSuperview];
    [&m_pAboutPageViewModule->GetAboutPageView() removeFromSuperview];
    [&m_pOptionsViewModule->GetOptionsView() removeFromSuperview];
    /*if(m_pApp->ToursEnabled())
    {
        [&m_pTourWebViewModule->GetTourWebView() removeFromSuperview];
    }*/
    
    
    // Initial experience layer
    [&m_pInitialExperienceIntroViewModule->GetIntroView() removeFromSuperview];
    
    Eegeo_DELETE m_pSurveyViewModule;
    
    Eegeo_DELETE m_pInteriorsExplorerViewModule;
    
    //Eegeo_DELETE m_pViewControllerUpdaterModule;
    
    Eegeo_DELETE m_pTourFullScreenImageViewModule;
    
    Eegeo_DELETE m_pTourExplorerViewModule;
    
    Eegeo_DELETE m_pMyPinDetailsViewModule;

    Eegeo_DELETE m_pMyPinCreationDetailsViewModule;

    Eegeo_DELETE m_pMyPinCreationConfirmationViewModule;
    
    Eegeo_DELETE m_pOptionsViewModule;
    
    Eegeo_DELETE m_pAboutPageViewModule;

    Eegeo_DELETE m_pCompassViewModule;

    Eegeo_DELETE m_pWorldPinOnMapViewModule;
    
    Eegeo_DELETE m_pTourWebViewModule;
    
    Eegeo_DELETE m_pSearchResultPoiViewModule;

    Eegeo_DELETE m_pModalBackgroundViewModule;

    Eegeo_DELETE m_pSearchResultSectionViewModule;
    
    Eegeo_DELETE m_pSearchMenuViewModule;
    
    Eegeo_DELETE m_pSettingsMenuViewModule;

    Eegeo_DELETE m_pFlattenButtonViewModule;
    
    Eegeo_DELETE m_pInitialExperienceIntroViewModule;
    
    //Eegeo_DELETE m_pWatermarkViewModule;
}

void AppHost::SetTouchExclusivity()
{
    [m_pView setTouchExclusivity:m_pView];
}

void AppHost::HandleFailureToProvideWorkingApiKey()
{
    m_wiring->Resolve<Eegeo::UI::NativeAlerts::IAlertBoxFactory>()->CreateSingleOptionAlertBox
    (
     "Bad API Key",
     "You must provide a valid API key to the constructor of EegeoWorld. See the readme file for details.",
     m_failAlertHandler
     );
}

void AppHost::HandleFailureToDownloadBootstrapResources()
{
    std::string message =
        m_wiring->Resolve<ExampleApp::Net::SdkModel::INetworkCapabilities>()->StreamOverWifiOnly()
        ? "Unable to download required data! Please ensure you have a Wi-fi connection the next time you attempt to run this application."
        : "Unable to download required data! Please ensure you have an Internet connection the next time you attempt to run this application.";

    m_wiring->Resolve<Eegeo::UI::NativeAlerts::IAlertBoxFactory>()->CreateSingleOptionAlertBox("Error", message, m_failAlertHandler);
}

void AppHost::HandleNoConnectivityWarning()
{
}

void AppHost::HandleInvalidConnectivityError()
{
    m_wiring->Resolve<Eegeo::UI::NativeAlerts::IAlertBoxFactory>()->CreateSingleOptionAlertBox
    (
     "Network error",
     "Unable to access web reliably. Please check your connection is valid & authenticated.",
     m_failAlertHandler
     );
}

void AppHost::HandleStartupFailure()
{
    exit(1);
}

void AppHost::HandleUserInteractionEnabledChanged(const ExampleApp::UserInteraction::UserInteractionEnabledChangedMessage& message)
{
    m_pView.userInteractionEnabled = message.IsEnabled();
}

