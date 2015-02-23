// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "App.h"
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
#include "SearchResultOnMapViewModule.h"
#include "SearchResultOnMapView.h"
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
#include "DefaultCommandsModule.h"
#include "DebugStats.h"
#include "iOSMemoryStats.h"
#include "GpsGlobeCameraController.h"

using namespace Eegeo::iOS;

AppHost::AppHost(
                 ViewController& viewController,
                 UIView* pView,
                 float displayWidth,
                 float displayHeight,
                 float deviceDpi,
                 float pixelScale
                 )

:m_pView(pView)
,m_viewController(viewController)
,m_pJpegLoader(NULL)
,m_pScreenProperties(NULL)
,m_piOSLocationService(NULL)
,m_iOSInputBoxFactory()
,m_iOSKeyboardInputFactory()
,m_iOSAlertBoxFactory()
,m_iOSNativeUIFactories(m_iOSAlertBoxFactory, m_iOSInputBoxFactory, m_iOSKeyboardInputFactory)
,m_piOSPlatformAbstractionModule(NULL)
,m_pApp(NULL)
,m_pMemoryStats(NULL)
{
    m_piOSLocationService = Eegeo_NEW(iOSLocationService)();
    
    m_pScreenProperties = Eegeo_NEW(Eegeo::Rendering::ScreenProperties)(displayWidth, displayHeight, pixelScale, deviceDpi);
    
    m_pJpegLoader = Eegeo_NEW(Eegeo::Helpers::Jpeg::JpegLoader)();
    
    m_piOSPlatformAbstractionModule = Eegeo_NEW(Eegeo::iOS::iOSPlatformAbstractionModule)(*m_pJpegLoader);
    
    Eegeo::EffectHandler::Initialise();
    
    Eegeo::Config::PlatformConfig platformConfig = Eegeo::iOS::iOSPlatformConfigBuilder(App::GetDevice(), App::IsDeviceMultiCore(), App::GetMajorSystemVersion()).Build();
    
    m_pInitialExperienceModule = Eegeo_NEW(ExampleApp::InitialExperience::iOSInitialExperienceModule)(m_iOSPersistentSettingsModel);
    
    m_pMemoryStats = Eegeo_NEW(Eegeo::iOS::iOSMemoryStats);
    
    m_pApp = Eegeo_NEW(ExampleApp::MobileExampleApp)(*m_piOSPlatformAbstractionModule,
                                                     *m_pScreenProperties,
                                                     *m_piOSLocationService,
                                                     m_iOSNativeUIFactories,
                                                     platformConfig,
                                                     *m_pJpegLoader,
                                                     *m_pInitialExperienceModule,
                                                     *m_pMemoryStats);
    
    
    CreateApplicationViewModules();
    
    m_pAppInputDelegate = Eegeo_NEW(AppInputDelegate)(*m_pApp, m_viewController, displayWidth, displayHeight, pixelScale);
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
    
    Eegeo_DELETE m_pMemoryStats;
    m_pMemoryStats = NULL;
    
    Eegeo_DELETE m_pInitialExperienceModule;
    m_pInitialExperienceModule = NULL;
    
    Eegeo_DELETE m_piOSLocationService;
    m_piOSLocationService = NULL;
    
    Eegeo_DELETE m_pScreenProperties;
    m_pScreenProperties = NULL;
    
    Eegeo_DELETE m_piOSPlatformAbstractionModule;
    m_piOSPlatformAbstractionModule = NULL;
    
    Eegeo_DELETE m_pJpegLoader;
    m_pJpegLoader = NULL;
    
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

void AppHost::SetViewportOffset(float x, float y)
{
}

void AppHost::Update(float dt)
{
    m_pApp->Update(dt);
    m_pViewControllerUpdaterModule->GetViewControllerUpdaterModel().UpdateObjects(dt);
}

void AppHost::Draw(float dt)
{
    m_pApp->Draw(dt);
}

bool AppHost::IsRunning()
{
    return m_pApp->IsRunning();
}

void AppHost::CreateApplicationViewModules()
{
    ExampleApp::MobileExampleApp& app = *m_pApp;
    
    m_pModalBackgroundViewModule = Eegeo_NEW(ExampleApp::ModalBackground::ModalBackgroundViewModule)(app.ModalityModule().GetModalityModel());
    
    
    m_pPrimaryMenuViewModule = Eegeo_NEW(ExampleApp::PrimaryMenu::PrimaryMenuViewModule)(app.PrimaryMenuModule().GetPrimaryMenuModel(),
                                                                                         app.PrimaryMenuModule().GetPrimaryMenuViewModel(),
                                                                                         *m_pScreenProperties,
                                                                                         app.ModalityModule().GetModalityModel());
    
    m_pSecondaryMenuViewModule = Eegeo_NEW(ExampleApp::SecondaryMenu::SecondaryMenuViewModule)(app.SecondaryMenuModule().GetSecondaryMenuModel(),
                                                                                               app.SecondaryMenuModule().GetSecondaryMenuViewModel(),
                                                                                               *m_pScreenProperties,
                                                                                               app.ModalityModule().GetModalityModel(),
                                                                                               app.SearchModule().GetSearchQueryPerformer(),
                                                                                               app.SearchModule().GetSearchService());
    
    m_pSearchResultMenuViewModule = Eegeo_NEW(ExampleApp::SearchResultMenu::SearchResultMenuViewModule)(app.SearchModule().GetSearchService(),
                                                                                                        app.SearchModule().GetSearchQueryPerformer(),
                                                                                                        app.CategorySearchModule().GetCategorySearchRepository(),
                                                                                                        app.SearchResultMenuModule().GetSearchResultMenuModel(),
                                                                                                        app.SearchResultMenuModule().GetMenuViewModel(),
                                                                                                        app.SearchResultMenuModule().GetSearchResultMenuViewModel(),
                                                                                                        *m_pScreenProperties,
                                                                                                        app.ModalityModule().GetModalityModel());
    
    m_pSearchResultPoiViewModule = Eegeo_NEW(ExampleApp::SearchResultPoi::SearchResultPoiViewModule)(app.SearchResultPoiModule().GetSearchResultPoiViewModel());
    
    m_pFlattenButtonViewModule = Eegeo_NEW(ExampleApp::FlattenButton::FlattenButtonViewModule)(app.FlattenButtonModule().GetFlattenButtonModel(),
                                                                                               app.FlattenButtonModule().GetFlattenButtonViewModel(),
                                                                                               *m_pScreenProperties);
    
    m_pSearchResultOnMapViewModule = Eegeo_NEW(ExampleApp::SearchResultOnMap::SearchResultOnMapViewModule)(app.SearchResultOnMapModule().GetSearchResultOnMapInFocusViewModel(),
                                                                                                           app.SearchResultOnMapModule().GetScreenControlViewModel(),
                                                                                                           app.ModalityModule().GetModalityModel(),
                                                                                                           app.PinDiameter(),
                                                                                                           m_pScreenProperties->GetPixelScale());
    
    
    m_pCompassViewModule = Eegeo_NEW(ExampleApp::Compass::CompassViewModule)(app.CompassModule().GetCompassModel(),
                                                                             app.CompassModule().GetCompassViewModel(),
                                                                             *m_pScreenProperties);
    
    m_pAboutPageViewModule = Eegeo_NEW(ExampleApp::AboutPage::AboutPageViewModule)(app.AboutPageModule().GetAboutPageModel(),
                                                                                   app.AboutPageModule().GetAboutPageViewModel());
    
    // 3d map view layer.
    [m_pView addSubview: &m_pSearchResultOnMapViewModule->GetSearchResultOnMapView()];
    
    // HUD behind modal background layer.
    [m_pView addSubview: &m_pFlattenButtonViewModule->GetFlattenButtonView()];
    [m_pView addSubview: &m_pCompassViewModule->GetCompassView()];
    
    // Modal background layer.
    [m_pView addSubview: &m_pModalBackgroundViewModule->GetModalBackgroundView()];
    
    // Menus & HUD layer.
    [m_pView addSubview: &m_pPrimaryMenuViewModule->GetPrimaryMenuView()];
    [m_pView addSubview: &m_pSecondaryMenuViewModule->GetSecondaryMenuView()];
    [m_pView addSubview: &m_pSearchResultMenuViewModule->GetSearchResultMenuView()];
    
    // Pop-up layer.
    [m_pView addSubview: &m_pSearchResultPoiViewModule->GetSearchResultPoiView()];
    [m_pView addSubview: &m_pAboutPageViewModule->GetAboutPageView()];
    
    m_pViewControllerUpdaterModule = Eegeo_NEW(ExampleApp::ViewControllerUpdater::ViewControllerUpdaterModule);
    ExampleApp::ViewControllerUpdater::IViewControllerUpdaterModel& viewControllerUpdaterModel = m_pViewControllerUpdaterModule->GetViewControllerUpdaterModel();
    
    viewControllerUpdaterModel.AddUpdateableObject(&m_pPrimaryMenuViewModule->GetPrimaryMenuViewController());
    viewControllerUpdaterModel.AddUpdateableObject(&m_pSecondaryMenuViewModule->GetSecondaryMenuViewController());
    viewControllerUpdaterModel.AddUpdateableObject(&m_pSearchResultMenuViewModule->GetSearchResultMenuViewController());
}

void AppHost::DestroyApplicationViewModules()
{
    // 3d map view layer.
    [&m_pSearchResultOnMapViewModule->GetSearchResultOnMapView() removeFromSuperview];
    
    // HUD behind modal background layer.
    [&m_pFlattenButtonViewModule->GetFlattenButtonView() removeFromSuperview];
    [&m_pCompassViewModule->GetCompassView() removeFromSuperview];
    
    // Modal background layer.
    [&m_pModalBackgroundViewModule->GetModalBackgroundView() removeFromSuperview];
    
    // Menus & HUD layer.
    [&m_pPrimaryMenuViewModule->GetPrimaryMenuView() removeFromSuperview];
    [&m_pSecondaryMenuViewModule->GetSecondaryMenuView() removeFromSuperview];
    [&m_pSearchResultMenuViewModule->GetSearchResultMenuView() removeFromSuperview];
    
    // Pop-up layer.
    [&m_pSearchResultPoiViewModule->GetSearchResultPoiView() removeFromSuperview];
    [&m_pAboutPageViewModule->GetAboutPageView() removeFromSuperview];
    
    Eegeo_DELETE m_pViewControllerUpdaterModule;
    
    Eegeo_DELETE m_pAboutPageViewModule;
    
    Eegeo_DELETE m_pCompassViewModule;
    
    Eegeo_DELETE m_pSearchResultOnMapViewModule;
    
    Eegeo_DELETE m_pSearchResultPoiViewModule;
    
    Eegeo_DELETE m_pModalBackgroundViewModule;
    
    Eegeo_DELETE m_pSearchResultMenuViewModule;
    
    Eegeo_DELETE m_pSecondaryMenuViewModule;
    
    Eegeo_DELETE m_pPrimaryMenuViewModule;
    
    Eegeo_DELETE m_pFlattenButtonViewModule;
}

