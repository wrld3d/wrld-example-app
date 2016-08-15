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
#include "ISettingsMenuModule.h"
#include "SettingsMenuViewModule.h"
#include "SettingsMenuView.h"
#include "ISearchMenuModule.h"
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
#include "IMyPinCreationModule.h"
#include "IPoiRingModule.h"
#include "IMyPinCreationDetailsModule.h"
#include "MyPinCreationDetailsViewModule.h"
#include "MyPinCreationDetailsView.h"
#include "MyPinDetailsViewModule.h"
#include "MyPinDetailsView.h"
#include "IMyPinDetailsModule.h"
#include "IMyPinsModule.h"
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
#include "IInteriorsExplorerModule.h"
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

#import "UIView+TouchExclusivity.h"

using namespace Eegeo::iOS;

class iOSAbstractionIoCModule
{
public:
    iOSAbstractionIoCModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder,
                            const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration)
    : m_builder(builder)
    , m_applicationConfiguration(applicationConfiguration)
    {
    }
    void Register()
    {
        m_builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
        {
            return std::make_shared<Eegeo::iOS::iOSPlatformAbstractionModule>(*(context.resolve<Eegeo::Helpers::Jpeg::IJpegLoader>()), m_applicationConfiguration.EegeoApiKey());
        }).as<Eegeo::Modules::IPlatformAbstractionModule>().singleInstance();
        
        // TODO, template out:
        
        m_builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
        {
            Eegeo::Modules::IPlatformAbstractionModule& module = *(context.resolve<Eegeo::Modules::IPlatformAbstractionModule>());
            return std::shared_ptr<Eegeo::Helpers::ITextureFileLoader>(&module.GetTextureFileLoader());
        }).singleInstance();
        
        m_builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
        {
            Eegeo::Modules::IPlatformAbstractionModule& module = *(context.resolve<Eegeo::Modules::IPlatformAbstractionModule>());
            return std::shared_ptr<Eegeo::Helpers::IHttpCache>(&module.GetHttpCache());
        }).singleInstance();
    }
    
private:
    const ExampleApp::ApplicationConfig::ApplicationConfiguration& m_applicationConfiguration;
    const std::shared_ptr<Hypodermic::ContainerBuilder> m_builder;
};

AppHost::AppHost(
    ViewController& viewController,
    UIView* pView,
    Eegeo::Rendering::ScreenProperties screenProperties,
    const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
    ExampleApp::Metrics::iOSFlurryMetricsService& metricsService
)

    :m_pView(pView)
    ,m_viewController(viewController)
    ,m_iOSInputBoxFactory()
    ,m_iOSKeyboardInputFactory()
    ,m_iOSAlertBoxFactory()
    ,m_iOSNativeUIFactories(m_iOSAlertBoxFactory, m_iOSInputBoxFactory, m_iOSKeyboardInputFactory)
    ,m_pApp(NULL)
    ,m_requestedApplicationInitialiseViewState(false)
    ,m_failAlertHandler(this, &AppHost::HandleStartupFailure)
    ,m_pTourWebViewModule(NULL)
    ,m_pTourFullScreenImageViewModule(NULL)
    ,m_pTourExplorerViewModule(NULL)
    ,m_userInteractionEnabledChangedHandler(this, &AppHost::HandleUserInteractionEnabledChanged)
{
    Eegeo::TtyHandler::TtyEnabled = true;
    
    m_containerBuilder = std::make_shared<Hypodermic::ContainerBuilder>();

    m_containerBuilder->registerInstance(std::shared_ptr<ExampleApp::Metrics::iOSFlurryMetricsService>(&metricsService)).as<ExampleApp::Metrics::IMetricsService>();
    m_containerBuilder->registerType<iOSLocationService>().as<Eegeo::Location::ILocationService>().singleInstance();
    m_containerBuilder->registerType<iOSConnectivityService>().as<Eegeo::Web::IConnectivityService>().singleInstance();
    m_containerBuilder->registerType<Eegeo::Helpers::Jpeg::JpegLoader>().as<Eegeo::Helpers::Jpeg::IJpegLoader>().singleInstance();
    m_containerBuilder->registerType<ExampleApp::ExampleAppMessaging::TMessageBus>().singleInstance();
    m_containerBuilder->registerType<ExampleApp::ExampleAppMessaging::TSdkModelDomainEventBus>().singleInstance();
    m_containerBuilder->registerType<ExampleApp::PersistentSettings::iOSPersistentSettingsModel>().as<ExampleApp::PersistentSettings::IPersistentSettingsModel>().singleInstance();

    iOSAbstractionIoCModule iosAbstractionModule(m_containerBuilder, applicationConfiguration);
    iosAbstractionModule.Register();
    
    m_containerBuilder->registerType<ExampleApp::InitialExperience::iOSInitialExperienceModule>().as<ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule>().singleInstance();
    
    m_containerBuilder->registerType<ExampleApp::Net::SdkModel::NetworkCapabilities>().as<ExampleApp::Net::SdkModel::INetworkCapabilities>().singleInstance();
    m_containerBuilder->registerType<ExampleApp::LinkOutObserver::LinkOutObserver>().singleInstance();
    m_containerBuilder->registerType<ExampleApp::URLRequest::View::URLRequestHandler>().singleInstance();
    
    m_pImageStore = [[ImageStore alloc]init];
    
    m_containerBuilder->registerType<ExampleApp::Menu::View::IOSMenuReactionModel>().as<ExampleApp::Menu::View::IMenuReactionModel>().singleInstance();
    
    Eegeo::iOS::iOSPlatformConfigBuilder iOSPlatformConfigBuilder(App::GetDevice(), App::IsDeviceMultiCore(), App::GetMajorSystemVersion());
    const Eegeo::Config::PlatformConfig& platformConfiguration = ExampleApp::ApplicationConfig::SdkModel::BuildPlatformConfig(iOSPlatformConfigBuilder, applicationConfiguration);
    
    m_containerBuilder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
                                                {
                                                    return std::make_shared<ExampleApp::MobileExampleApp>(
                                                        applicationConfiguration,
                                                        *(context.resolve<Eegeo::Modules::IPlatformAbstractionModule>()),
                                                        screenProperties,
                                                        *(context.resolve<Eegeo::Location::ILocationService>()),
                                                        m_iOSNativeUIFactories,
                                                        platformConfiguration,
                                                        *(context.resolve<Eegeo::Helpers::Jpeg::IJpegLoader>()),
                                                        *(context.resolve<ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule>()),
                                                        *(context.resolve<ExampleApp::PersistentSettings::IPersistentSettingsModel>()),
                                                        *(context.resolve<ExampleApp::ExampleAppMessaging::TMessageBus>()),
                                                        *(context.resolve<ExampleApp::ExampleAppMessaging::TSdkModelDomainEventBus>()),
                                                        *(context.resolve<ExampleApp::Net::SdkModel::INetworkCapabilities>()),
                                                        *(context.resolve<ExampleApp::Metrics::IMetricsService>()),
                                                        *this,
                                                        *(context.resolve<ExampleApp::Menu::View::IMenuReactionModel>())
                                                      );
                                                }).singleInstance();
    
    
    m_containerBuilder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
                                                {
                                                    return std::make_shared<AppLocationDelegate>(context.resolve<iOSLocationService>(), m_viewController);
                                                }).singleInstance();
    
    
    // TODO : More to put in the container past here...
    
    m_container = m_containerBuilder->build();
    m_container->resolve<ExampleApp::LinkOutObserver::LinkOutObserver>()->OnAppStart();
    
    m_pApp = (m_container->resolve<ExampleApp::MobileExampleApp>()).get();
    
    CreateApplicationViewModules(screenProperties);

    m_pAppInputDelegate = Eegeo_NEW(AppInputDelegate)(*m_pApp, m_viewController, screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight(), screenProperties.GetPixelScale());

    Eegeo::EffectHandler::Initialise();
    GetMessageBus().SubscribeUi(m_userInteractionEnabledChangedHandler);
}

ExampleApp::ExampleAppMessaging::TMessageBus& AppHost::GetMessageBus()
{
    return *(m_container->resolve<ExampleApp::ExampleAppMessaging::TMessageBus>());
}

ExampleApp::ExampleAppMessaging::TSdkModelDomainEventBus& AppHost::GetSdkMessageBus()
{
    return *(m_container->resolve<ExampleApp::ExampleAppMessaging::TSdkModelDomainEventBus>());
}

AppHost::~AppHost()
{
    GetMessageBus().UnsubscribeUi(m_userInteractionEnabledChangedHandler);
    
    Eegeo_DELETE m_pAppInputDelegate;
    m_pAppInputDelegate = NULL;

    DestroyApplicationViewModules();
    
    Eegeo_DELETE m_pApp;
    m_pApp = NULL;
    
    [m_pImageStore release];
    m_pImageStore = nil;

    Eegeo::EffectHandler::Reset();
    Eegeo::EffectHandler::Shutdown();
}

void AppHost::OnResume()
{
    m_container->resolve<ExampleApp::LinkOutObserver::LinkOutObserver>()->OnAppResume();
    
    m_pApp->OnResume();
}

void AppHost::OnPause()
{
    m_pApp->OnPause();
}

void AppHost::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
{
    m_pApp->NotifyScreenPropertiesChanged(screenProperties);
}

void AppHost::Update(float dt)
{
    if (!m_container->resolve<AppLocationDelegate>()->HasReceivedPermissionResponse())
    {
        return;
    }

    if(m_pApp->IsLoadingScreenComplete() && !m_requestedApplicationInitialiseViewState)
    {
        m_requestedApplicationInitialiseViewState = true;
        m_pApp->InitialiseApplicationViewState();
    }

    m_pApp->Update(dt);
    m_pViewControllerUpdaterModule->GetViewControllerUpdaterModel().UpdateObjectsUiThread(dt);

    GetMessageBus().FlushToUi();
    GetMessageBus().FlushToNative();
}

void AppHost::Draw(float dt)
{
    m_pApp->Draw(dt);
}

bool AppHost::IsRunning()
{
    return m_pApp->IsRunning();
}

void AppHost::CreateApplicationViewModules(const Eegeo::Rendering::ScreenProperties& screenProperties)
{
    ExampleApp::MobileExampleApp& app = *m_pApp;
    
    m_pWatermarkViewModule = Eegeo_NEW(ExampleApp::Watermark::View::WatermarkViewModule)(app.WatermarkModule().GetWatermarkViewModel(),
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
    
    SetTouchExclusivity();
}

void AppHost::DestroyApplicationViewModules()
{
    // 3d map view layer.
    [&m_pWorldPinOnMapViewModule->GetWorldPinOnMapView() removeFromSuperview];
    
    [&m_pInitialExperienceIntroViewModule->GetIntroBackgroundView() removeFromSuperview];

    // HUD behind modal background layer.
    [&m_pWatermarkViewModule->GetWatermarkView() removeFromSuperview];
    [&m_pFlattenButtonViewModule->GetFlattenButtonView() removeFromSuperview];
    [&m_pCompassViewModule->GetCompassView() removeFromSuperview];
    [&m_pMyPinCreationInitiationViewModule->GetMyPinCreationInitiationView() removeFromSuperview];
    [&m_pMyPinCreationConfirmationViewModule->GetMyPinCreationConfirmationView() removeFromSuperview];
    if(m_pApp->ToursEnabled())
    {
        [&m_pTourFullScreenImageViewModule->GetTourFullScreenImageView() removeFromSuperview];
        [&m_pTourExplorerViewModule->GetTourExplorerView() removeFromSuperview];
    }
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
    if(m_pApp->ToursEnabled())
    {
        [&m_pTourWebViewModule->GetTourWebView() removeFromSuperview];
    }
    
    
    // Initial experience layer
    [&m_pInitialExperienceIntroViewModule->GetIntroView() removeFromSuperview];
    
    Eegeo_DELETE m_pSurveyViewModule;
    
    Eegeo_DELETE m_pInteriorsExplorerViewModule;
    
    Eegeo_DELETE m_pViewControllerUpdaterModule;
    
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
    
    Eegeo_DELETE m_pWatermarkViewModule;
}

void AppHost::SetTouchExclusivity()
{
    [m_pView setTouchExclusivity:m_pView];
}

void AppHost::HandleFailureToProvideWorkingApiKey()
{
    m_iOSAlertBoxFactory.CreateSingleOptionAlertBox
    (
     "Bad API Key",
     "You must provide a valid API key to the constructor of EegeoWorld. See the readme file for details.",
     m_failAlertHandler
     );
}

void AppHost::HandleFailureToDownloadBootstrapResources()
{
    std::string message =
        m_container->resolve<ExampleApp::Net::SdkModel::INetworkCapabilities>()->StreamOverWifiOnly()
        ? "Unable to download required data! Please ensure you have a Wi-fi connection the next time you attempt to run this application."
        : "Unable to download required data! Please ensure you have an Internet connection the next time you attempt to run this application.";

    m_iOSAlertBoxFactory.CreateSingleOptionAlertBox("Error", message, m_failAlertHandler);
}

void AppHost::HandleNoConnectivityWarning()
{
}

void AppHost::HandleInvalidConnectivityError()
{
    m_iOSAlertBoxFactory.CreateSingleOptionAlertBox
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

