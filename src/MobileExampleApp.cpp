// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MobileExampleApp.h"
#include "GlobeCameraTouchController.h"
#include "RenderCamera.h"
#include "GpsGlobeCameraController.h"
#include "GlobeCameraInterestPointProvider.h"
#include "CameraHelpers.h"
#include "LatLongAltitude.h"
#include "IWorldPinsService.h"
#include "ISearchRefreshService.h"
#include "GpsGlobeCameraControllerFactory.h"
#include "GlobeCameraTouchSettings.h"
#include "GlobeCameraController.h"
#include "GpsGlobeCameraComponentConfiguration.h"
#include "ITextureFileLoader.h"
#include "IWeatherMenuModule.h"
#include "CompassUpdateController.h"
#include "CameraTransitionController.h"
#include "WorldAreaLoaderModule.h"
#include "IInitialExperienceModel.h"
#include "IInitialExperienceController.h"
#include "CategorySearchModule.h"
#include "AboutPageModule.h"
#include "RenderContext.h"
#include "ScreenProperties.h"
#include "TerrainModelModule.h"
#include "MapModule.h"
#include "CityThemesModule.h"
#include "RenderingModule.h"
#include "StreamingModule.h"
#include "EnvironmentCharacterSet.h"
#include "Blitter.h"
#include "IPoiRingTouchController.h"
#include "MyPinCreationModule.h"
#include "ISearchResultMenuViewModel.h"
#include "PoiRingModule.h"
#include "IPoiRingController.h"
#include "MyPinCreationDetailsModule.h"
#include "MyPinsModule.h"
#include "IWorldPinsInFocusController.h"
#include "IWorldPinsScaleController.h"
#include "MyPinDetailsModule.h"

namespace ExampleApp
{
    const std::string ApiKey = "OBTAIN API_KEY FROM https://appstore.eegeo.com AND INSERT IT HERE";
    const std::string DecartaApiKey = "OBTAIN DECARTA SEARCH KEY AND INSERT IT HERE";
    
	namespace
	{
		Eegeo::Rendering::LoadingScreen* CreateLoadingScreen(const Eegeo::Rendering::ScreenProperties& screenProperties,
		        const Eegeo::Modules::Core::RenderingModule& renderingModule,
		        const Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule)
		{
			Eegeo::Rendering::LoadingScreenConfig loadingScreenConfig;
			loadingScreenConfig.layout = Eegeo::Rendering::LoadingScreenLayout::Centred;
			loadingScreenConfig.backgroundColor = Eegeo::v4::One();
			loadingScreenConfig.loadingBarColor = Eegeo::v4(135.0f/255.0f, 213.0f/255.f, 245.0f/255.f, 1.0f);
			loadingScreenConfig.loadingBarBackgroundColor = Eegeo::v4(0.5f, 0.5f, 0.5f, 1.0f);
			loadingScreenConfig.fadeOutDurationSeconds = 1.5f;
			loadingScreenConfig.screenWidth = screenProperties.GetScreenWidth();
			loadingScreenConfig.screenHeight = screenProperties.GetScreenHeight();


			Eegeo::Rendering::LoadingScreen* loadingScreen = Eegeo::Rendering::LoadingScreen::Create(
			            "SplashScreen.png",
			            loadingScreenConfig,
			            renderingModule.GetShaderIdGenerator(),
			            renderingModule.GetMaterialIdGenerator(),
			            renderingModule.GetGlBufferPool(),
			            renderingModule.GetVertexLayoutPool(),
			            renderingModule.GetVertexBindingPool(),
			            platformAbstractionModule.GetTextureFileLoader());

			return loadingScreen;
		}
	}

	MobileExampleApp::MobileExampleApp(
	    Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
	    Eegeo::Rendering::ScreenProperties screenProperties,
	    Eegeo::Location::ILocationService& locationService,
	    Eegeo::UI::NativeUIFactories& nativeUIFactories,
	    Eegeo::Config::PlatformConfig platformConfig,
	    Eegeo::Helpers::Jpeg::IJpegLoader& jpegLoader,
	    ExampleApp::InitialExperience::IInitialExperienceModule& initialExperienceModule,
        ExampleApp::PersistentSettings::IPersistentSettingsModel& persistentSettings,
	    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
	    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
		: m_pGlobeCameraController(NULL)
		, m_pCameraTouchController(NULL)
        , m_pWorld(NULL)
		, m_pNavigationService(NULL)
		, m_platformAbstractions(platformAbstractions)
		, m_pLoadingScreen(NULL)
        , m_pBlitter(NULL)
        , m_screenProperties(screenProperties)
		, m_initialisedApplicationViewState(false)
        , m_pinDiameter(50.f)
		, m_pCameraTransitionController(NULL)
		, m_pPrimaryMenuModule(NULL)
		, m_pSecondaryMenuModule(NULL)
		, m_pSearchResultMenuModule(NULL)
		, m_pModalityModule(NULL)
		, m_pCategorySearchModule(NULL)
		, m_pFlattenButtonModule(NULL)
		, m_pSearchModule(NULL)
		, m_pPinIconsTexturePageLayout(NULL)
		, m_pPinsModule(NULL)
		, m_pWorldPinsModule(NULL)
		, m_pSearchResultOnMapModule(NULL)
		, m_pReactionModelModule(NULL)
		, m_pReactionControllerModule(NULL)
		, m_pSearchResultPoiModule(NULL)
		, m_pPlaceJumpsModule(NULL)
		, m_pWeatherMenuModule(NULL)
		, m_pCompassModule(NULL)
		, m_pWorldAreaLoaderModule(NULL)
		, m_pAboutPageModule(NULL)
		, m_initialExperienceModule(initialExperienceModule)
		, m_uiToNativeMessageBus(uiToNativeMessageBus)
		, m_nativeToUiMessageBus(nativeToUiMessageBus)
        , m_persistentSettings(persistentSettings)
        , m_pMyPinCreationModule(NULL)
        , m_pPoiRingModule(NULL)
        , m_pMyPinCreationDetailsModule(NULL)
        , m_pMyPinsModule(NULL)
        , m_pMyPinDetailsModule(NULL)
	{
		m_pBlitter = Eegeo_NEW(Eegeo::Blitter)(1024 * 128, 1024 * 64, 1024 * 32);
		m_pBlitter->Initialise();

		m_pWorld = Eegeo_NEW(Eegeo::EegeoWorld)(ApiKey,
		                                        m_platformAbstractions,
		                                        jpegLoader,
		                                        screenProperties,
		                                        locationService,
		                                        *m_pBlitter,
		                                        nativeUIFactories,
		                                        Eegeo::EnvironmentCharacterSet::Latin,
		                                        platformConfig,
		                                        NULL);

		Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = m_pWorld->GetTerrainModelModule();
		Eegeo::Modules::Map::MapModule& mapModule = m_pWorld->GetMapModule();

		m_pNavigationService = Eegeo_NEW(Eegeo::Location::NavigationService)(&m_pWorld->GetLocationService(),
		                       &terrainModelModule.GetTerrainHeightProvider());

		Eegeo::Camera::GlobeCamera::GpsGlobeCameraControllerFactory cameraControllerFactory(terrainModelModule.GetTerrainHeightProvider(),
		        mapModule.GetEnvironmentFlatteningService(),
		        mapModule.GetResourceCeilingProvider(),
		        *m_pNavigationService);


		const bool useLowSpecSettings = false;

		Eegeo::Camera::GlobeCamera::GpsGlobeCameraComponentConfiguration gpsGlobeCameraConfig = Eegeo::Camera::GlobeCamera::GpsGlobeCameraComponentConfiguration::CreateDefault();
		gpsGlobeCameraConfig.panToUnlockThreshold =  0.03f;
		Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchControllerConfig = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
		Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration globeCameraConfig = Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration::CreateDefault(useLowSpecSettings);

		m_pGlobeCameraController = cameraControllerFactory.Create(gpsGlobeCameraConfig, touchControllerConfig, globeCameraConfig);

		m_pCameraTouchController = &m_pGlobeCameraController->GetTouchController();

		Eegeo::Camera::RenderCamera* renderCamera = m_pGlobeCameraController->GetCamera();
		renderCamera->SetViewport(0.f, 0.f, screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());

		Eegeo::Camera::GlobeCamera::GlobeCameraTouchSettings touchSettings = m_pGlobeCameraController->GetGlobeCameraController().GetTouchSettings();
		touchSettings.TiltEnabled = true;
		m_pGlobeCameraController->GetGlobeCameraController().SetTouchSettings(touchSettings);

		float interestPointLatitudeDegrees = 37.7858f;
		float interestPointLongitudeDegrees = -122.401f;
		float interestPointAltitudeMeters = 2.7;

		Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude::FromDegrees(interestPointLatitudeDegrees,
		        interestPointLongitudeDegrees,
		        interestPointAltitudeMeters);

		float cameraControllerOrientationDegrees = 0.0f;
		float cameraControllerDistanceFromInterestPointMeters = 1781.0f;

		Eegeo::Space::EcefTangentBasis cameraInterestBasis;
		Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(location.ToECEF(), cameraControllerOrientationDegrees, cameraInterestBasis);

		m_pGlobeCameraController->SetView(cameraInterestBasis, cameraControllerDistanceFromInterestPointMeters);

		m_pCameraTransitionController = Eegeo_NEW(ExampleApp::CameraTransitions::CameraTransitionController)(*m_pGlobeCameraController, *m_pNavigationService);

		CreateApplicationModelModules();

		m_pLoadingScreen = CreateLoadingScreen(screenProperties, m_pWorld->GetRenderingModule(), m_pWorld->GetPlatformAbstractionModule());
	}

	MobileExampleApp::~MobileExampleApp()
	{
		DestroyApplicationModelModules();

		Eegeo_DELETE m_pCameraTransitionController;
		Eegeo_DELETE m_pNavigationService;
		Eegeo_DELETE m_pGlobeCameraController;
		Eegeo_DELETE m_pLoadingScreen;

		Eegeo_DELETE m_pWorld;

		m_pBlitter->Shutdown();
		Eegeo_DELETE m_pBlitter;
		m_pBlitter = NULL;
	}

	void MobileExampleApp::CreateApplicationModelModules()
	{
		Eegeo::EegeoWorld& world = *m_pWorld;

		m_pReactionControllerModule = Eegeo_NEW(ExampleApp::Reaction::ReactionControllerModule)();

		m_pAboutPageModule = Eegeo_NEW(ExampleApp::AboutPage::AboutPageModule)(m_identityProvider,
		                     m_pReactionControllerModule->GetReactionControllerModel());

		m_pSearchModule = Eegeo_NEW(ExampleApp::Search::SearchModule)(DecartaApiKey,
		                  m_platformAbstractions.GetWebLoadRequestFactory(),
		                  m_platformAbstractions.GetUrlEncoder(),
		                  *m_pGlobeCameraController,
		                  *m_pCameraTransitionController,
		                  m_uiToNativeMessageBus,
		                  m_nativeToUiMessageBus);

		m_pCompassModule = Eegeo_NEW(ExampleApp::Compass::CompassModule)(*m_pNavigationService,
		                   *m_pGlobeCameraController,
		                   m_identityProvider,
		                   m_uiToNativeMessageBus,
		                   m_nativeToUiMessageBus);

		Eegeo::Modules::Map::CityThemesModule& cityThemesModule = world.GetCityThemesModule();

		m_pWeatherMenuModule = Eegeo_NEW(ExampleApp::WeatherMenu::WeatherMenuModule)(m_platformAbstractions.GetFileIO(),
		                       cityThemesModule.GetCityThemesService(),
		                       cityThemesModule.GetCityThemesUpdater(),
		                       m_uiToNativeMessageBus);

		m_pPrimaryMenuModule = Eegeo_NEW(ExampleApp::PrimaryMenu::PrimaryMenuModule)(m_identityProvider,
		                       AboutPageModule().GetAboutPageViewModel(),
		                       m_pReactionControllerModule->GetReactionControllerModel());

		m_pSecondaryMenuModule = Eegeo_NEW(ExampleApp::SecondaryMenu::SecondaryMenuModule)(m_identityProvider,
		                         m_pReactionControllerModule->GetReactionControllerModel(),
		                         m_pSearchModule->GetSearchQueryPerformer(),
		                         m_uiToNativeMessageBus);

		m_pPlaceJumpsModule = Eegeo_NEW(ExampleApp::PlaceJumps::PlaceJumpsModule)(m_platformAbstractions.GetFileIO(),
		                      GetCameraController(),
		                      m_pCompassModule->GetCompassModel(),
		                      m_pSecondaryMenuModule->GetSecondaryMenuViewModel(),
		                      m_uiToNativeMessageBus);

		m_pCategorySearchModule = Eegeo_NEW(ExampleApp::CategorySearch::CategorySearchModule(
		                                        SearchModule().GetSearchQueryPerformer(),
		                                        m_pSecondaryMenuModule->GetSecondaryMenuViewModel(),
		                                        m_uiToNativeMessageBus));

		m_pSecondaryMenuModule->AddMenuSection("Search", "place", m_pCategorySearchModule->GetCategorySearchMenuModel(), true);
		m_pSecondaryMenuModule->AddMenuSection("Weather", "weather", m_pWeatherMenuModule->GetWeatherMenuModel(), true);
		m_pSecondaryMenuModule->AddMenuSection("Locations", "location", m_pPlaceJumpsModule->GetPlaceJumpsMenuModel(), true);

		Eegeo::Modules::Map::MapModule& mapModule = world.GetMapModule();

		m_pFlattenButtonModule = Eegeo_NEW(ExampleApp::FlattenButton::FlattenButtonModule)(mapModule.GetEnvironmentFlatteningService(),
		                         m_identityProvider,
		                         m_uiToNativeMessageBus,
		                         m_nativeToUiMessageBus);

		InitialisePinsModules(mapModule, world);

		m_pSearchResultPoiModule = Eegeo_NEW(ExampleApp::SearchResultPoi::SearchResultPoiModule)(m_identityProvider,
		                           m_pReactionControllerModule->GetReactionControllerModel());

		m_pSearchResultMenuModule = Eegeo_NEW(ExampleApp::SearchResultMenu::SearchResultMenuModule)(
		                                m_pSearchModule->GetSearchResultRepository(),
		                                m_pSearchModule->GetSearchQueryPerformer(),
		                                m_identityProvider,
		                                *m_pCameraTransitionController,
		                                m_pReactionControllerModule->GetReactionControllerModel(),
		                                m_uiToNativeMessageBus,
		                                m_nativeToUiMessageBus
		                            );

		m_pSearchResultOnMapModule = Eegeo_NEW(ExampleApp::SearchResultOnMap::SearchResultOnMapModule)(m_pSearchModule->GetSearchResultRepository(),
                                                                                                       m_pSearchResultPoiModule->GetSearchResultPoiViewModel(),
                                                                                                       m_pWorldPinsModule->GetWorldPinsService(),
                                                                                                       m_nativeToUiMessageBus);
        
        m_pMyPinsModule = Eegeo_NEW(ExampleApp::MyPins::MyPinsModule)(m_pWorldPinsModule->GetWorldPinsService(),
                                                                      m_platformAbstractions,
                                                                      m_persistentSettings,
                                                                      m_pPrimaryMenuModule->GetPrimaryMenuViewModel(),
                                                                      m_uiToNativeMessageBus,
                                                                      m_nativeToUiMessageBus,
                                                                      *m_pCameraTransitionController);
        
        m_pPrimaryMenuModule->AddMenuSection("My Pins", "place", m_pMyPinsModule->GetMyPinsMenuModel(), true);
        
        m_pMyPinCreationModule = Eegeo_NEW(ExampleApp::MyPinCreation::MyPinCreationModule)(m_pMyPinsModule->GetMyPinsService(),
                                                                                           m_identityProvider,
                                                                                           m_pPrimaryMenuModule->GetPrimaryMenuViewModel(),
                                                                                           m_pSecondaryMenuModule->GetSecondaryMenuViewModel(),
                                                                                           m_pSearchModule->GetSearchQueryPerformer(),
                                                                                           m_pSearchResultMenuModule->GetMenuViewModel(),
                                                                                           m_nativeToUiMessageBus,
                                                                                           m_uiToNativeMessageBus,
                                                                                           m_pReactionControllerModule->GetReactionControllerModel());
        
        m_pPoiRingModule = Eegeo_NEW(ExampleApp::MyPinCreation::PoiRing::PoiRingModule)(m_pMyPinCreationModule->GetMyPinCreationModel(),
                                                                                        m_platformAbstractions,
                                                                                        m_pWorld->GetRenderingModule(),
                                                                                        m_pWorld->GetAsyncLoadersModule(),
                                                                                        m_pWorld->GetLightingModule(),
                                                                                        m_pWorld->GetTerrainModelModule(),
                                                                                        m_pWorld->GetMapModule());


        m_pMyPinCreationDetailsModule = Eegeo_NEW(ExampleApp::MyPinCreationDetails::MyPinCreationDetailsModule)(m_identityProvider,
                                                                                                          m_pReactionControllerModule->GetReactionControllerModel());
        
        m_pMyPinDetailsModule = Eegeo_NEW(ExampleApp::MyPinDetails::MyPinDetailsModule)(m_identityProvider,
                                                                                        m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                        m_pMyPinsModule->GetMyPinsService(),
                                                                                        m_nativeToUiMessageBus,
                                                                                        m_uiToNativeMessageBus);

		std::vector<ExampleApp::ScreenControlViewModel::IScreenControlViewModel*> reactors(GetReactorControls());
		std::vector<ExampleApp::OpenableControlViewModel::IOpenableControlViewModel*> openables(GetOpenableControls());

		m_pModalityModule = Eegeo_NEW(ExampleApp::Modality::ModalityModule)(m_uiToNativeMessageBus, openables);

		m_pReactionModelModule = Eegeo_NEW(ExampleApp::Reaction::ReactionModelModule)(m_pReactionControllerModule->GetReactionControllerModel(),
		                         openables,
		                         reactors);

		Eegeo::Modules::Map::StreamingModule& streamingModule = world.GetStreamingModule();
		m_pWorldAreaLoaderModule = Eegeo_NEW(WorldAreaLoader::WorldAreaLoaderModule)(streamingModule.GetPrecachingService());

		m_initialExperienceModule.InitialiseWithApplicationModels(m_pWorldAreaLoaderModule->GetWorldAreaLoaderModel());
	}

	void MobileExampleApp::DestroyApplicationModelModules()
	{
        Eegeo_DELETE m_pMyPinDetailsModule;
        
        Eegeo_DELETE m_pMyPinCreationModule;
        
        Eegeo_DELETE m_pPoiRingModule;
        
        Eegeo_DELETE m_pMyPinsModule;
        
		m_initialExperienceModule.TearDown();

		Eegeo_DELETE m_pWorldAreaLoaderModule;

		Eegeo_DELETE m_pReactionModelModule;

		Eegeo_DELETE m_pSearchResultMenuModule;

		Eegeo_DELETE m_pModalityModule;

		Eegeo_DELETE m_pSearchResultOnMapModule;

		Eegeo_DELETE m_pSearchResultPoiModule;

		Eegeo_DELETE m_pWorldPinsModule;

		Eegeo_DELETE m_pPinsModule;

		Eegeo_DELETE m_pPlaceJumpsModule;

		Eegeo_DELETE m_pCategorySearchModule;

		Eegeo_DELETE m_pSecondaryMenuModule;

		Eegeo_DELETE m_pPrimaryMenuModule;

		Eegeo_DELETE m_pFlattenButtonModule;

		Eegeo_DELETE m_pWeatherMenuModule;

		Eegeo_DELETE m_pCompassModule;

		Eegeo_DELETE m_pSearchModule;

		Eegeo_DELETE m_pAboutPageModule;

		Eegeo_DELETE m_pReactionControllerModule;
	}

	std::vector<ExampleApp::OpenableControlViewModel::IOpenableControlViewModel*> MobileExampleApp::GetOpenableControls() const
	{
		std::vector<ExampleApp::OpenableControlViewModel::IOpenableControlViewModel*> openables;
		openables.push_back(&PrimaryMenuModule().GetPrimaryMenuViewModel());
		openables.push_back(&SecondaryMenuModule().GetSecondaryMenuViewModel());
		openables.push_back(&SearchResultMenuModule().GetMenuViewModel());
		openables.push_back(&SearchResultPoiModule().GetObservableOpenableControl());
		openables.push_back(&AboutPageModule().GetObservableOpenableControl());
        openables.push_back(&MyPinCreationDetailsModule().GetObservableOpenableControl());
        openables.push_back(&MyPinDetailsModule().GetObservableOpenableControl());
        openables.push_back(&MyPinCreationModule().GetObservableOpenableControl());
		return openables;
	}

	std::vector<ExampleApp::ScreenControlViewModel::IScreenControlViewModel*> MobileExampleApp::GetReactorControls() const
	{
		std::vector<ExampleApp::ScreenControlViewModel::IScreenControlViewModel*> reactors;
		reactors.push_back(&PrimaryMenuModule().GetPrimaryMenuViewModel());
		reactors.push_back(&SecondaryMenuModule().GetSecondaryMenuViewModel());
		reactors.push_back(&SearchResultMenuModule().GetMenuViewModel());
		reactors.push_back(&FlattenButtonModule().GetScreenControlViewModel());
		reactors.push_back(&WorldPinsModule().GetScreenControlViewModel());
		reactors.push_back(&CompassModule().GetScreenControlViewModel());
        reactors.push_back(&MyPinCreationModule().GetInitiationScreenControlViewModel());
		return reactors;
	}

	void MobileExampleApp::InitialisePinsModules(Eegeo::Modules::Map::MapModule& mapModule, Eegeo::EegeoWorld& world)
	{
		m_platformAbstractions.GetTextureFileLoader().LoadTexture(m_pinIconsTexture, "SearchResultOnMap/PinIconTexturePage.png", true);
		Eegeo_ASSERT(m_pinIconsTexture.textureId != 0);

		int numberOfTilesAlongEachAxisOfTexturePage = 4;
		m_pPinIconsTexturePageLayout = Eegeo_NEW(Eegeo::Rendering::RegularTexturePageLayout)(numberOfTilesAlongEachAxisOfTexturePage);

		int spriteWidth = m_pinDiameter;
		int spriteHeight = m_pinDiameter;

		Eegeo::Modules::Core::RenderingModule& renderingModule = world.GetRenderingModule();
		Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = world.GetTerrainModelModule();

		m_pPinsModule = Eegeo_NEW(Eegeo::Pins::PinsModule)(
		                    m_pinIconsTexture.textureId,
		                    *m_pPinIconsTexturePageLayout,
		                    renderingModule.GetGlBufferPool(),
		                    renderingModule.GetShaderIdGenerator(),
		                    renderingModule.GetMaterialIdGenerator(),
		                    renderingModule.GetVertexBindingPool(),
		                    renderingModule.GetVertexLayoutPool(),
		                    renderingModule.GetRenderableFilters(),
		                    terrainModelModule.GetTerrainHeightProvider(),
		                    spriteWidth,
		                    spriteHeight,
		                    Eegeo::Rendering::LayerIds::PlaceNames,
		                    mapModule.GetEnvironmentFlatteningService()
		                );

		m_pWorldPinsModule = Eegeo_NEW(ExampleApp::WorldPins::WorldPinsModule)(m_pPinsModule->GetRepository(),
                                                                               m_pPinsModule->GetController(),
                                                                               mapModule.GetEnvironmentFlatteningService(),
                                                                               m_identityProvider,
                                                                               m_nativeToUiMessageBus,
                                                                               m_uiToNativeMessageBus);
	}

	void MobileExampleApp::OnPause()
	{
		Eegeo::EegeoWorld& eegeoWorld = World();
		eegeoWorld.OnPause();
	}

	void MobileExampleApp::OnResume()
	{
		Eegeo::EegeoWorld& eegeoWorld = World();
		eegeoWorld.OnResume();
	}

	void MobileExampleApp::Update(float dt)
	{
		Eegeo::EegeoWorld& eegeoWorld(World());
        Eegeo::dv3 ecefInterestPoint(m_pGlobeCameraController->GetEcefInterestPoint());
        Eegeo::Camera::RenderCamera& renderCamera(*m_pGlobeCameraController->GetCamera());

		eegeoWorld.EarlyUpdate(dt);

		m_pGlobeCameraController->Update(dt);
		m_pCameraTransitionController->Update(dt);
        
        m_pPoiRingModule->GetPoiRingController().Update(dt, renderCamera, ecefInterestPoint);

		eegeoWorld.Update(dt, renderCamera, ecefInterestPoint);

		m_pSearchModule->GetSearchRefreshService().TryRefreshSearch(dt, ecefInterestPoint);

		m_pPinsModule->GetController().Update(dt, renderCamera);

		if(!eegeoWorld.Initialising())
		{
            WorldPinsModule().GetWorldPinsScaleController().Update(dt, renderCamera);
			CompassModule().GetCompassUpdateController().Update(dt);
		}

		m_pNavigationService->Update(dt);

		UpdateLoadingScreen(dt);
	}

	void MobileExampleApp::Draw (float dt)
	{
        Eegeo::EegeoWorld& eegeoWorld = World();
        Eegeo::dv3 ecefInterestPoint(m_pGlobeCameraController->GetEcefInterestPoint());
        Eegeo::Camera::RenderCamera& renderCamera(*m_pGlobeCameraController->GetCamera());

		if(!eegeoWorld.Initialising())
		{
            WorldPinsModule().GetWorldPinsInFocusController().Update(dt, ecefInterestPoint, renderCamera);
		}

		eegeoWorld.Draw(renderCamera, m_screenProperties);

		if (m_pLoadingScreen != NULL)
		{
			m_pLoadingScreen->Draw();
		}
	}
    
    void MobileExampleApp::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
        m_screenProperties = screenProperties;
        m_pGlobeCameraController->GetCamera()->SetViewport(0.f, 0.f, screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());
        if (m_pLoadingScreen != NULL)
        {
            m_pLoadingScreen->NotifyScreenDimensionsChanged(screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());
        }
    }

	void MobileExampleApp::InitialiseApplicationViewState()
	{
		Eegeo_ASSERT(m_initialisedApplicationViewState == false, "Can only initialise application state once!\n");

		m_initialisedApplicationViewState = true;

		m_pPrimaryMenuModule->GetPrimaryMenuViewModel().AddToScreen();
		m_pSecondaryMenuModule->GetSecondaryMenuViewModel().AddToScreen();
		m_pSearchResultMenuModule->GetMenuViewModel().AddToScreen();
		m_pFlattenButtonModule->GetScreenControlViewModel().AddToScreen();
		m_pCompassModule->GetScreenControlViewModel().AddToScreen();
        m_pMyPinCreationModule->GetInitiationScreenControlViewModel().AddToScreen();
	}

	void MobileExampleApp::UpdateLoadingScreen(float dt)
	{
		if (m_pLoadingScreen == NULL)
		{
			return;
		}

		Eegeo::EegeoWorld& eegeoWorld = World();

		if (!eegeoWorld.Initialising() && !m_pLoadingScreen->IsDismissed())
		{
			m_pLoadingScreen->Dismiss();
		}

		m_pLoadingScreen->SetProgress(eegeoWorld.GetInitialisationProgress());
		m_pLoadingScreen->Update(dt);

		if (!m_pLoadingScreen->IsVisible())
		{
			Eegeo_DELETE m_pLoadingScreen;
			m_pLoadingScreen = NULL;

			InitialExperience::IInitialExperienceModel& initialExperienceModel = m_initialExperienceModule.GetInitialExperienceModel();
			if(!initialExperienceModel.HasCompletedInitialExperience())
			{
				InitialExperience::IInitialExperienceController& initialExperienceController = m_initialExperienceModule.GetInitialExperienceController();
				initialExperienceController.Update(dt);
			}
		}
	}

	bool MobileExampleApp::IsRunning() const
	{
		return !m_pWorld->Initialising();
	}

    void MobileExampleApp::Event_TouchRotate(const AppInterface::RotateData& data)
    {
        if(World().Initialising())
        {
            return;
        }
        
        m_pCameraTouchController->Event_TouchRotate(data);
    }

    void MobileExampleApp::Event_TouchRotate_Start(const AppInterface::RotateData& data)
    {
        if(World().Initialising())
        {
            return;
        }
        
        m_pCameraTouchController->Event_TouchRotate_Start(data);
    }

    void MobileExampleApp::Event_TouchRotate_End(const AppInterface::RotateData& data)
    {
        if(World().Initialising())
        {
            return;
        }
        
        m_pCameraTouchController->Event_TouchRotate_End(data);
    }

    void MobileExampleApp::Event_TouchPinch(const AppInterface::PinchData& data)
    {
        if(World().Initialising())
        {
            return;
        }
        
        m_pCameraTouchController->Event_TouchPinch(data);
    }

    void MobileExampleApp::Event_TouchPinch_Start(const AppInterface::PinchData& data)
    {
        if(World().Initialising())
        {
            return;
        }
        
        m_pCameraTouchController->Event_TouchPinch_Start(data);
    }

    void MobileExampleApp::Event_TouchPinch_End(const AppInterface::PinchData& data)
    {
        if(World().Initialising())
        {
            return;
        }
        
        m_pCameraTouchController->Event_TouchPinch_End(data);
    }

    void MobileExampleApp::Event_TouchPan(const AppInterface::PanData& data)
    {
        MyPinCreation::PoiRing::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if(World().Initialising() || poiRingTouchController.IsDragging())
        {
            return;
        }
        
        m_pCameraTouchController->Event_TouchPan(data);
    }

    void MobileExampleApp::Event_TouchPan_Start(const AppInterface::PanData& data)
    {
        MyPinCreation::PoiRing::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if(World().Initialising() || poiRingTouchController.IsDragging())
        {
            return;
        }
        
        m_pCameraTouchController->Event_TouchPan_Start(data);
    }

    void MobileExampleApp::Event_TouchPan_End(const AppInterface::PanData& data)
    {
        MyPinCreation::PoiRing::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if(World().Initialising() || poiRingTouchController.IsDragging())
        {
            return;
        }
        
        m_pCameraTouchController->Event_TouchPan_End(data);
    }

    void MobileExampleApp::Event_TouchTap(const AppInterface::TapData& data)
    {
        if(World().Initialising())
        {
            return;
        }
        
        if(!m_pWorldPinsModule->GetWorldPinsService().HandleTouchTap(data.point))
        {
            m_pCameraTouchController->Event_TouchTap(data);
        }
    }

    void MobileExampleApp::Event_TouchDoubleTap(const AppInterface::TapData& data)
    {
        if(World().Initialising())
        {
            return;
        }
        
        m_pCameraTouchController->Event_TouchDoubleTap(data);
    }

    void MobileExampleApp::Event_TouchDown(const AppInterface::TouchData& data)
    {
        if(World().Initialising())
        {
            return;
        }
        
        MyPinCreation::PoiRing::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if (!poiRingTouchController.HandleTouchDown(data, *m_pGlobeCameraController->GetCamera(), m_pGlobeCameraController->GetGlobeCameraController()))
        {
            m_pCameraTouchController->Event_TouchDown(data);
        }
        
    }

    void MobileExampleApp::Event_TouchMove(const AppInterface::TouchData& data)
    {
        if(World().Initialising())
        {
            return;
        }
        
        MyPinCreation::PoiRing::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if (!poiRingTouchController.HandleTouchMove(data, *m_pGlobeCameraController->GetCamera(), m_pGlobeCameraController->GetGlobeCameraController()))
        {
            m_pCameraTouchController->Event_TouchMove(data);
        }
    }

    void MobileExampleApp::Event_TouchUp(const AppInterface::TouchData& data)
    {
        if(World().Initialising())
        {
            return;
        }
        
        MyPinCreation::PoiRing::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if (!poiRingTouchController.HandleTouchUp(data))
        {
            m_pCameraTouchController->Event_TouchUp(data);
        }
    }
}
