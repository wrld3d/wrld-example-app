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
#include "PrimaryMenuViewModule.h"
#include "PrimaryMenuView.h"
#include "SecondaryMenuViewModule.h"
#include "SecondaryMenuView.h"
#include "ModalBackgroundView.h"
#include "FlattenButtonView.h"
#include "FlattenButtonViewModule.h"
#include "WorldPinOnMapViewModule.h"
#include "WorldPinOnMapView.h"
#include "SearchResultPoiViewModule.h"
#include "SearchResultPoiView.h"
#include "SearchResultMenuView.h"
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

using namespace Eegeo::iOS;

AppHost::AppHost(
    ViewController& viewController,
    UIView* pView,
    Eegeo::Rendering::ScreenProperties screenProperties
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
{
    m_piOSLocationService = Eegeo_NEW(iOSLocationService)();

    m_piOSConnectivityService = Eegeo_NEW(iOSConnectivityService)();

    m_pJpegLoader = Eegeo_NEW(Eegeo::Helpers::Jpeg::JpegLoader)();

    m_piOSPlatformAbstractionModule = Eegeo_NEW(Eegeo::iOS::iOSPlatformAbstractionModule)(*m_pJpegLoader, ExampleApp::ApiKey);

    Eegeo::EffectHandler::Initialise();

    Eegeo::Config::PlatformConfig platformConfig = Eegeo::iOS::iOSPlatformConfigBuilder(App::GetDevice(), App::IsDeviceMultiCore(), App::GetMajorSystemVersion()).Build();
    platformConfig.OptionsConfig.StartMapModuleAutomatically = false;

    m_pInitialExperienceModule = Eegeo_NEW(ExampleApp::InitialExperience::iOSInitialExperienceModule)(m_iOSPersistentSettingsModel);

    m_pApp = Eegeo_NEW(ExampleApp::MobileExampleApp)(ExampleApp::ApiKey,
             *m_piOSPlatformAbstractionModule,
             screenProperties,
             *m_piOSLocationService,
             m_iOSNativeUIFactories,
             platformConfig,
             *m_pJpegLoader,
             *m_pInitialExperienceModule,
             m_iOSPersistentSettingsModel,
             m_messageBus);

    CreateApplicationViewModules(screenProperties);

    m_pAppInputDelegate = Eegeo_NEW(AppInputDelegate)(*m_pApp, m_viewController, screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight(), screenProperties.GetPixelScale());
    m_pAppLocationDelegate = Eegeo_NEW(AppLocationDelegate)(*m_piOSLocationService, m_viewController);
}

AppHost::~AppHost()
{
    Eegeo_DELETE m_pAppLocationDelegate;
    m_pAppLocationDelegate = NULL;

    Eegeo_DELETE m_pAppInputDelegate;
    m_pAppInputDelegate = NULL;

    DestroyApplicationViewModules();

    Eegeo_DELETE m_pApp;
    m_pApp = NULL;

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

    m_pModalBackgroundViewModule = Eegeo_NEW(ExampleApp::ModalBackground::View::ModalBackgroundViewModule)(app.ModalityModule().GetModalityModel(), screenProperties);


    m_pPrimaryMenuViewModule = Eegeo_NEW(ExampleApp::PrimaryMenu::View::PrimaryMenuViewModule)(app.MyPinsModule().GetMyPinsMenuModel(),
                               app.PrimaryMenuModule().GetPrimaryMenuViewModel(),
                               screenProperties,
                               app.ModalityModule().GetModalityModel());

    m_pSecondaryMenuViewModule = Eegeo_NEW(ExampleApp::SecondaryMenu::View::SecondaryMenuViewModule)(app.SecondaryMenuModule().GetSecondaryMenuModel(),
                                 app.SecondaryMenuModule().GetSecondaryMenuViewModel(),
                                 screenProperties,
                                 m_messageBus);

    m_pSearchResultMenuViewModule = Eegeo_NEW(ExampleApp::SearchResultMenu::View::SearchResultMenuViewModule)(app.CategorySearchModule().GetCategorySearchRepository(),
                                    app.SearchResultMenuModule().GetSearchResultMenuModel(),
                                    app.SearchResultMenuModule().GetMenuViewModel(),
                                    app.SearchResultMenuModule().GetSearchResultMenuViewModel(),
                                    screenProperties,
                                    m_messageBus);

    m_pSearchResultPoiViewModule = Eegeo_NEW(ExampleApp::SearchResultPoi::View::SearchResultPoiViewModule)(app.SearchResultPoiModule().GetSearchResultPoiViewModel());

    m_pFlattenButtonViewModule = Eegeo_NEW(ExampleApp::FlattenButton::View::FlattenButtonViewModule)(
                                     app.FlattenButtonModule().GetFlattenButtonViewModel(),
                                     screenProperties,
                                     m_messageBus);

    m_pWorldPinOnMapViewModule = Eegeo_NEW(ExampleApp::WorldPins::View::WorldPinOnMapViewModule)(app.WorldPinsModule().GetWorldPinInFocusViewModel(),
                                 app.WorldPinsModule().GetScreenControlViewModel(),
                                 app.ModalityModule().GetModalityModel(),
                                 app.PinDiameter(),
                                 screenProperties.GetPixelScale());


    m_pCompassViewModule = Eegeo_NEW(ExampleApp::Compass::View::CompassViewModule)(app.CompassModule().GetCompassViewModel(),
                           screenProperties,
                           m_messageBus);

    m_pAboutPageViewModule = Eegeo_NEW(ExampleApp::AboutPage::View::AboutPageViewModule)(app.AboutPageModule().GetAboutPageViewModel());

    m_pMyPinCreationInitiationViewModule = Eegeo_NEW(ExampleApp::MyPinCreation::View::MyPinCreationInitiationViewModule)(m_messageBus,
                                           app.MyPinCreationModule().GetMyPinCreationInitiationViewModel(),
                                           app.MyPinCreationModule().GetMyPinCreationConfirmationViewModel(),
                                           screenProperties);

    m_pMyPinCreationConfirmationViewModule = Eegeo_NEW(ExampleApp::MyPinCreation::View::MyPinCreationConfirmationViewModule)(m_messageBus,
            app.MyPinCreationModule().GetMyPinCreationConfirmationViewModel(),
            app.MyPinCreationModule().GetMyPinCreationCompositeViewModel(),
            app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
            screenProperties);

    m_pMyPinCreationDetailsViewModule = Eegeo_NEW(ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsViewModule)(
                                            m_messageBus,
                                            app.MyPinCreationDetailsModule().GetMyPinCreationDetailsViewModel(),
                                            screenProperties,
                                            *m_piOSConnectivityService,
                                                                                                                          &m_viewController);

    m_pMyPinDetailsViewModule = Eegeo_NEW(ExampleApp::MyPinDetails::View::MyPinDetailsViewModule)(m_messageBus,
                                app.MyPinDetailsModule().GetMyPinDetailsViewModel(),
                                screenProperties);

    // 3d map view layer.
    [m_pView addSubview: &m_pWorldPinOnMapViewModule->GetWorldPinOnMapView()];

    // HUD behind modal background layer.
    [m_pView addSubview: &m_pFlattenButtonViewModule->GetFlattenButtonView()];
    [m_pView addSubview: &m_pCompassViewModule->GetCompassView()];
    [m_pView addSubview: &m_pMyPinCreationInitiationViewModule->GetMyPinCreationInitiationView()];
    [m_pView addSubview: &m_pMyPinCreationConfirmationViewModule->GetMyPinCreationConfirmationView()];

    // Modal background layer.
    [m_pView addSubview: &m_pModalBackgroundViewModule->GetModalBackgroundView()];

    // Menus & HUD layer.
    [m_pView addSubview: &m_pPrimaryMenuViewModule->GetPrimaryMenuView()];
    [m_pView addSubview: &m_pSecondaryMenuViewModule->GetSecondaryMenuView()];
    [m_pView addSubview: &m_pSearchResultMenuViewModule->GetSearchResultMenuView()];

    // Pop-up layer.
    [m_pView addSubview: &m_pSearchResultPoiViewModule->GetView()];
    [m_pView addSubview: &m_pAboutPageViewModule->GetAboutPageView()];
    [m_pView addSubview: &m_pMyPinCreationDetailsViewModule->GetMyPinCreationDetailsView()];
    [m_pView addSubview: &m_pMyPinDetailsViewModule->GetMyPinDetailsView()];

    m_pViewControllerUpdaterModule = Eegeo_NEW(ExampleApp::ViewControllerUpdater::View::ViewControllerUpdaterModule);
    ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModel& viewControllerUpdaterModel = m_pViewControllerUpdaterModule->GetViewControllerUpdaterModel();

    viewControllerUpdaterModel.AddUpdateableObject(m_pPrimaryMenuViewModule->GetMenuController());
    viewControllerUpdaterModel.AddUpdateableObject(m_pSecondaryMenuViewModule->GetMenuController());
    viewControllerUpdaterModel.AddUpdateableObject(m_pSearchResultMenuViewModule->GetMenuController());
}

void AppHost::DestroyApplicationViewModules()
{
    // 3d map view layer.
    [&m_pWorldPinOnMapViewModule->GetWorldPinOnMapView() removeFromSuperview];

    // HUD behind modal background layer.
    [&m_pFlattenButtonViewModule->GetFlattenButtonView() removeFromSuperview];
    [&m_pCompassViewModule->GetCompassView() removeFromSuperview];
    [&m_pMyPinCreationInitiationViewModule->GetMyPinCreationInitiationView() removeFromSuperview];
    [&m_pMyPinCreationConfirmationViewModule->GetMyPinCreationConfirmationView() removeFromSuperview];

    // Modal background layer.
    [&m_pModalBackgroundViewModule->GetModalBackgroundView() removeFromSuperview];

    // Menus & HUD layer.
    [&m_pPrimaryMenuViewModule->GetPrimaryMenuView() removeFromSuperview];
    [&m_pSecondaryMenuViewModule->GetSecondaryMenuView() removeFromSuperview];
    [&m_pSearchResultMenuViewModule->GetSearchResultMenuView() removeFromSuperview];

    // Pop-up layer.
    [&m_pMyPinDetailsViewModule->GetMyPinDetailsView() removeFromSuperview];
    [&m_pMyPinCreationDetailsViewModule->GetMyPinCreationDetailsView() removeFromSuperview];
    [&m_pSearchResultPoiViewModule->GetView() removeFromSuperview];
    [&m_pAboutPageViewModule->GetAboutPageView() removeFromSuperview];

    Eegeo_DELETE m_pViewControllerUpdaterModule;

    Eegeo_DELETE m_pMyPinDetailsViewModule;

    Eegeo_DELETE m_pMyPinCreationDetailsViewModule;

    Eegeo_DELETE m_pMyPinCreationConfirmationViewModule;

    Eegeo_DELETE m_pViewControllerUpdaterModule;

    Eegeo_DELETE m_pAboutPageViewModule;

    Eegeo_DELETE m_pCompassViewModule;

    Eegeo_DELETE m_pWorldPinOnMapViewModule;

    Eegeo_DELETE m_pSearchResultPoiViewModule;

    Eegeo_DELETE m_pModalBackgroundViewModule;

    Eegeo_DELETE m_pSearchResultMenuViewModule;

    Eegeo_DELETE m_pSecondaryMenuViewModule;

    Eegeo_DELETE m_pPrimaryMenuViewModule;

    Eegeo_DELETE m_pFlattenButtonViewModule;
}

