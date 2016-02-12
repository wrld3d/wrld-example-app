// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "App.h"
#include "MenuController.h"
#include "AppHost.h"
#include "LatLongAltitude.h"
#include "EegeoWorld.h"
#include "ScreenProperties.h"
#include "AppInterface.h"
#include "Blitter.h"
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
#include "iOSYelpSearchServiceModule.h"
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

#import "UIView+TouchExclusivity.h"

using namespace Eegeo::iOS;

AppHost::AppHost(
    ViewController& viewController,
    UIView* pView,
    Eegeo::Rendering::ScreenProperties screenProperties,
    const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
    ExampleApp::Metrics::iOSFlurryMetricsService& metricsService
)

    :m_pView(pView)
    ,m_viewController(viewController)
    ,m_pJpegLoader(NULL)
    ,m_piOSLocationService(NULL)
    ,m_piOSConnectivityService(NULL)
    ,m_iOSInputBoxFactory()
    ,m_iOSKeyboardInputFactory()
    ,m_iOSAlertBoxFactory()
    ,m_iOSNativeUIFactories(m_iOSAlertBoxFactory, m_iOSInputBoxFactory, m_iOSKeyboardInputFactory)
    ,m_piOSPlatformAbstractionModule(NULL)
    ,m_pApp(NULL)
    ,m_requestedApplicationInitialiseViewState(false)
    ,m_searchServiceModules()
    ,m_iOSFlurryMetricsService(metricsService)
    ,m_failAlertHandler(this, &AppHost::HandleStartupFailure)
    ,m_pTourWebViewModule(NULL)
    ,m_pTourFullScreenImageViewModule(NULL)
    ,m_pTourExplorerViewModule(NULL)
    ,m_userInteractionEnabledChangedHandler(this, &AppHost::HandleUserInteractionEnabledChanged)
    ,m_pLinkOutObserver(NULL)
    ,m_pURLRequestHandler(NULL)
{
    Eegeo::TtyHandler::TtyEnabled = true;
    
    m_piOSLocationService = Eegeo_NEW(iOSLocationService)();

    m_piOSConnectivityService = Eegeo_NEW(iOSConnectivityService)();

    m_pJpegLoader = Eegeo_NEW(Eegeo::Helpers::Jpeg::JpegLoader)();

    m_piOSPlatformAbstractionModule = Eegeo_NEW(Eegeo::iOS::iOSPlatformAbstractionModule)(*m_pJpegLoader, ExampleApp::ApiKey);

    Eegeo::EffectHandler::Initialise();

    Eegeo::Config::PlatformConfig platformConfig = Eegeo::iOS::iOSPlatformConfigBuilder(App::GetDevice(), App::IsDeviceMultiCore(), App::GetMajorSystemVersion()).Build();
    platformConfig.OptionsConfig.StartMapModuleAutomatically = false;
    platformConfig.CityThemesConfig.EmbeddedThemeManifestFile = "embedded_manifest.txt";
    platformConfig.CityThemesConfig.EmbeddedThemeTexturePath = "Textures/EmbeddedTheme";
    platformConfig.CityThemesConfig.EmbeddedThemeNameContains = "Summer";
    platformConfig.CityThemesConfig.EmbeddedThemeStateName = "DayDefault";

    m_pInitialExperienceModule = Eegeo_NEW(ExampleApp::InitialExperience::iOSInitialExperienceModule)(m_iOSPersistentSettingsModel, m_messageBus);
    
    m_pNetworkCapabilities = Eegeo_NEW(ExampleApp::Net::SdkModel::NetworkCapabilities)(*m_piOSConnectivityService,
                                                                                       m_piOSPlatformAbstractionModule->GetHttpCache(),
                                                                                       m_iOSPersistentSettingsModel);
    
    m_searchServiceModules[ExampleApp::Search::YelpVendorName] = Eegeo_NEW(ExampleApp::Search::Yelp::iOSYelpSearchServiceModule)(m_piOSPlatformAbstractionModule->GetWebLoadRequestFactory(),
                                                                                                 *m_pNetworkCapabilities,
                                                                                                 m_piOSPlatformAbstractionModule->GetUrlEncoder());
    
    m_pLinkOutObserver = Eegeo_NEW(ExampleApp::LinkOutObserver::LinkOutObserver)(m_iOSFlurryMetricsService,
                                                                                 m_iOSPersistentSettingsModel);
    
    m_pLinkOutObserver->OnAppStart();
    
    m_pURLRequestHandler = Eegeo_NEW(ExampleApp::URLRequest::View::URLRequestHandler)(m_messageBus,
                                                                                      *m_pLinkOutObserver);
    
    m_pImageStore = [[ImageStore alloc]init];
    
    m_pApp = Eegeo_NEW(ExampleApp::MobileExampleApp)(ExampleApp::ApiKey,
             *m_piOSPlatformAbstractionModule,
             screenProperties,
             *m_piOSLocationService,
             m_iOSNativeUIFactories,
             platformConfig,
             *m_pJpegLoader,
             *m_pInitialExperienceModule,
             m_iOSPersistentSettingsModel,
             m_messageBus,
             m_sdkModelDomainEventBus,
             *m_pNetworkCapabilities,
             m_searchServiceModules,
             m_iOSFlurryMetricsService,
             applicationConfiguration,
             *this);

    CreateApplicationViewModules(screenProperties);

    m_pAppInputDelegate = Eegeo_NEW(AppInputDelegate)(*m_pApp, m_viewController, screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight(), screenProperties.GetPixelScale());
    m_pAppLocationDelegate = Eegeo_NEW(AppLocationDelegate)(*m_piOSLocationService, m_viewController);
    
    m_messageBus.SubscribeUi(m_userInteractionEnabledChangedHandler);
}

AppHost::~AppHost()
{
    m_messageBus.UnsubscribeUi(m_userInteractionEnabledChangedHandler);
    
    Eegeo_DELETE m_pAppLocationDelegate;
    m_pAppLocationDelegate = NULL;

    Eegeo_DELETE m_pAppInputDelegate;
    m_pAppInputDelegate = NULL;

    DestroyApplicationViewModules();
    
    Eegeo_DELETE m_pApp;
    m_pApp = NULL;
    
    [m_pImageStore release];
    m_pImageStore = nil;
    
    Eegeo_DELETE m_pURLRequestHandler;
    m_pURLRequestHandler = NULL;
    
    Eegeo_DELETE m_pLinkOutObserver;
    m_pLinkOutObserver = NULL;
    
    for(std::map<std::string, ExampleApp::Search::SdkModel::ISearchServiceModule*>::iterator it = m_searchServiceModules.begin(); it != m_searchServiceModules.end(); ++it)
    {
        Eegeo_DELETE (*it).second;
    }
    m_searchServiceModules.clear();
    
    Eegeo_DELETE m_pNetworkCapabilities;
    m_pNetworkCapabilities = NULL;

    Eegeo_DELETE m_pInitialExperienceModule;
    m_pInitialExperienceModule = NULL;

    Eegeo_DELETE m_piOSLocationService;
    m_piOSLocationService = NULL;

    Eegeo_DELETE m_piOSPlatformAbstractionModule;
    m_piOSPlatformAbstractionModule = NULL;

    Eegeo_DELETE m_pJpegLoader;
    m_pJpegLoader = NULL;

    Eegeo_DELETE m_piOSConnectivityService;
    m_piOSConnectivityService = NULL;

    Eegeo::EffectHandler::Reset();
    Eegeo::EffectHandler::Shutdown();
}

void AppHost::OnResume()
{
    m_pLinkOutObserver->OnAppResume();
    
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
    Eegeo::Modules::Map::MapModule& mapModule = m_pApp->World().GetMapModule();
    if (!mapModule.IsRunning() && m_pAppLocationDelegate->HasReceivedPermissionResponse())
    {
        mapModule.Start();
    }

    if(m_pApp->IsLoadingScreenComplete() && !m_requestedApplicationInitialiseViewState)
    {
        m_requestedApplicationInitialiseViewState = true;
        m_pApp->InitialiseApplicationViewState();
    }

    m_pApp->Update(dt);
    m_pViewControllerUpdaterModule->GetViewControllerUpdaterModel().UpdateObjectsUiThread(dt);

    m_messageBus.FlushToUi();
    m_messageBus.FlushToNative();
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
                                                                                         m_messageBus,
                                                                                         m_iOSFlurryMetricsService);

    m_pModalBackgroundViewModule = Eegeo_NEW(ExampleApp::ModalBackground::View::ModalBackgroundViewModule)(app.ModalityModule().GetModalityModel(), screenProperties);
    
    m_pSettingsMenuViewModule = Eegeo_NEW(ExampleApp::SettingsMenu::View::SettingsMenuViewModule)(app.SettingsMenuModule().GetSettingsMenuModel(),
                                                                                                  app.SettingsMenuModule().GetSettingsMenuViewModel(),
                                                                                                  screenProperties,
                                                                                                  m_pModalBackgroundViewModule->GetModalBackgroundViewInterop(),
                                                                                                  m_messageBus);
    
    m_pSearchMenuViewModule = Eegeo_NEW(ExampleApp::SearchMenu::View::SearchMenuViewModule)(app.SearchMenuModule().GetSearchMenuModel(),
                                                                                            app.SearchMenuModule().GetSearchMenuViewModel(),
                                                                                            app.SearchMenuModule().GetSearchSectionViewModel(),
                                                                                            screenProperties,
                                                                                            app.CategorySearchModule().GetCategorySearchRepository(),
                                                                                            m_pModalBackgroundViewModule->GetModalBackgroundViewInterop(),
                                                                                            m_messageBus);
    
    m_pSearchResultSectionViewModule = Eegeo_NEW(ExampleApp::SearchResultSection::View::SearchResultSectionViewModule)(app.SearchMenuModule().GetSearchMenuViewModel(),
                                                                                                                       app.SearchResultSectionModule().GetSearchResultSectionOptionsModel(),
                                                                                                                       app.SearchResultSectionModule().GetSearchResultSectionOrder(),
                                                                                                                       m_messageBus);

    m_pSearchResultPoiViewModule = Eegeo_NEW(ExampleApp::SearchResultPoi::View::SearchResultPoiViewModule)(app.SearchResultPoiModule().GetSearchResultPoiViewModel(),
                                                                                                           m_messageBus,
                                                                                                           m_iOSFlurryMetricsService);

    m_pFlattenButtonViewModule = Eegeo_NEW(ExampleApp::FlattenButton::View::FlattenButtonViewModule)(
                                     app.FlattenButtonModule().GetFlattenButtonViewModel(),
                                     screenProperties,
                                     m_messageBus,
                                     m_iOSFlurryMetricsService);

    m_pWorldPinOnMapViewModule = Eegeo_NEW(ExampleApp::WorldPins::View::WorldPinOnMapViewModule)(app.WorldPinsModule().GetWorldPinInFocusViewModel(),
                                 app.WorldPinsModule().GetScreenControlViewModel(),
                                 app.ModalityModule().GetModalityModel(),
                                 app.PinDiameter(),
                                 screenProperties.GetPixelScale(),
                                 m_pImageStore);
    
    m_pCompassViewModule = Eegeo_NEW(ExampleApp::Compass::View::CompassViewModule)(app.CompassModule().GetCompassViewModel(),
                           screenProperties,
                           m_messageBus);

    m_pAboutPageViewModule = Eegeo_NEW(ExampleApp::AboutPage::View::AboutPageViewModule)(app.AboutPageModule().GetAboutPageViewModel(), m_iOSFlurryMetricsService);
    
    m_pOptionsViewModule = Eegeo_NEW(ExampleApp::Options::View::OptionsViewModule)(app.OptionsModule().GetOptionsViewModel(),
                                                                                   m_piOSPlatformAbstractionModule->GetiOSHttpCache(),
                                                                                   m_messageBus,
                                                                                   app.World().GetWorkPool());

    m_pMyPinCreationInitiationViewModule = Eegeo_NEW(ExampleApp::MyPinCreation::View::MyPinCreationInitiationViewModule)(m_messageBus,
                                           app.MyPinCreationModule().GetMyPinCreationInitiationViewModel(),
                                           app.MyPinCreationModule().GetMyPinCreationConfirmationViewModel(),
                                           screenProperties,
                                           m_iOSFlurryMetricsService);

    m_pMyPinCreationConfirmationViewModule = Eegeo_NEW(ExampleApp::MyPinCreation::View::MyPinCreationConfirmationViewModule)(m_messageBus,
            app.MyPinCreationModule().GetMyPinCreationConfirmationViewModel(),
            app.MyPinCreationModule().GetMyPinCreationCompositeViewModel(),
            app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
            screenProperties,
            m_iOSFlurryMetricsService);

    m_pMyPinCreationDetailsViewModule = Eegeo_NEW(ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsViewModule)(
                                            m_messageBus,
                                            app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
                                            screenProperties,
                                            m_iOSFlurryMetricsService,
                                            &m_viewController);

    m_pMyPinDetailsViewModule = Eegeo_NEW(ExampleApp::MyPinDetails::View::MyPinDetailsViewModule)(m_messageBus,
                                app.MyPinDetailsModule().GetMyPinDetailsViewModel(),
                                screenProperties);
    
    
    if(app.ToursEnabled())
    {
        m_pTourWebViewModule = Eegeo_NEW(ExampleApp::Tours::View::TourWeb::TourWebViewModule)(screenProperties);
        
        m_pTourExplorerViewModule = Eegeo_NEW(ExampleApp::Tours::View::TourExplorer::TourExplorerViewModule)
                                                                                           (m_messageBus,
                                                                                            app.ToursModule().GetToursExplorerViewModel(),
                                                                                            *m_pURLRequestHandler,
                                                                                            app.ToursModule().GetToursExplorerCompositeViewController(),
                                                                                            screenProperties,
                                                                                            m_pImageStore);
    
        m_pTourFullScreenImageViewModule = Eegeo_NEW(ExampleApp::Tours::View::TourFullScreenImage::TourFullScreenImageViewModule)(app.ToursModule().GetTourFullScreenImageViewModel(),
                                                                                                                                  screenProperties);
    }
    
    m_pInitialExperienceIntroViewModule = Eegeo_NEW(ExampleApp::InitialExperience::View::InitialExperienceIntroViewModule)(m_messageBus);
    
    
    m_pInteriorsExplorerViewModule = Eegeo_NEW(ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewModule)(app.InteriorsExplorerModule().GetInteriorsExplorerViewModel(),
                                                                                             m_messageBus,
                                                                                             app.MyPinCreationModule().GetMyPinCreationInitiationViewModel(),
                                                                                             app.SettingsMenuModule().GetSettingsMenuViewModel(),
                                                                                             app.SearchMenuModule().GetSearchMenuViewModel(),
                                                                                             app.FlattenButtonModule().GetScreenControlViewModel(),
                                                                                             app.CompassModule().GetScreenControlViewModel(),
                                                                                             screenProperties,
                                                                                             app.GetIdentityProvider());
    
    m_pSurveyViewModule = Eegeo_NEW(ExampleApp::Surveys::View::SurveyViewModule)(m_messageBus,
                                                                                 m_iOSFlurryMetricsService,
                                                                                 *m_pURLRequestHandler);
    
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
        m_pNetworkCapabilities->StreamOverWifiOnly()
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

