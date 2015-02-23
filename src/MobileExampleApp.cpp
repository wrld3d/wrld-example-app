// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

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

#include "GlobeCameraJumpController.h"
#include "ResourceNodeCache.h"

#include "IRouteCreator.h"
#include "FrustumStreamingVolume.h"
#include "MapDebugModule.h"

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
#include "QuadTreeCube.h"
#include "LodRefinementConfig.h"
#include "StreamingVolumeController.h"
#include "GpsMarkerModule.h"
#include "IGpsMarkerController.h"
#include "InitialExperienceDialogsModule.h"
#include "ApiKey.h"
#include "INetworkCapabilities.h"
#include "FlurryWrapper.h"

namespace ExampleApp
{
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
            loadingScreenConfig.loadingBarOffset = Eegeo::v2(0.5f, 0.1f);
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
        const std::string& apiKey,
        Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
        Eegeo::Rendering::ScreenProperties& screenProperties,
        Eegeo::Location::ILocationService& locationService,
        Eegeo::UI::NativeUIFactories& nativeUIFactories,
        Eegeo::Config::PlatformConfig platformConfig,
        Eegeo::Helpers::Jpeg::IJpegLoader& jpegLoader,
        ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule& initialExperienceModule,
        ExampleApp::PersistentSettings::IPersistentSettingsModel& persistentSettings,
        Eegeo::Debug::IMemoryStats& memoryStats,
        ExampleAppMessaging::TMessageBus& messageBus,
        Net::SdkModel::INetworkCapabilities& networkCapabilities)
        : m_pGlobeCameraController(NULL)
        , m_pCameraTouchController(NULL)
        , m_pNavigationService(NULL)
        , m_pWorld(NULL)
        , m_platformAbstractions(platformAbstractions, networkCapabilities)
        , m_pLoadingScreen(NULL)
        , m_pinDiameter(50.f)
        , m_initialisedApplicationViewState(false)
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
        , m_pGpsMarkerModule(NULL)
        , m_pWorldAreaLoaderModule(NULL)
        , m_pAboutPageModule(NULL)
        , m_initialExperienceModule(initialExperienceModule)
        , m_pBlitter(NULL)
        , m_messageBus(messageBus)
        , m_persistentSettings(persistentSettings)
        , m_pMyPinCreationModule(NULL)
        , m_pPoiRingModule(NULL)
        , m_pMyPinCreationDetailsModule(NULL)
        , m_pMyPinsModule(NULL)
        , m_pMyPinDetailsModule(NULL)
    	, m_pInitialExperienceDialogsModule(NULL)
        , m_pOptionsModule(NULL)
        , m_screenProperties(screenProperties)
        , m_networkCapabilities(networkCapabilities)
        , m_setFlurryLocation(false)
    {
        FLURRY_BEGIN(FlurryApiKey.c_str(), EEGEO_PLATFORM_VERSION_NUMBER);

        m_pBlitter = Eegeo_NEW(Eegeo::Blitter)(1024 * 128, 1024 * 64, 1024 * 32);
        m_pBlitter->Initialise();

        m_pWorld = Eegeo_NEW(Eegeo::EegeoWorld)(apiKey,
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

        m_pGlobeCameraController = cameraControllerFactory.Create(gpsGlobeCameraConfig, touchControllerConfig, globeCameraConfig, m_screenProperties);

        m_pCameraTouchController = &m_pGlobeCameraController->GetTouchController();

        Eegeo::Camera::GlobeCamera::GlobeCameraTouchSettings touchSettings = m_pGlobeCameraController->GetGlobeCameraController().GetTouchSettings();
        touchSettings.TiltEnabled = true;
        m_pGlobeCameraController->GetGlobeCameraController().SetTouchSettings(touchSettings);

        float interestPointLatitudeDegrees = 37.7858f;
        float interestPointLongitudeDegrees = -122.401f;
        float interestPointAltitudeMeters = 2.7f;

        Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude::FromDegrees(interestPointLatitudeDegrees,
                interestPointLongitudeDegrees,
                interestPointAltitudeMeters);

        float cameraControllerOrientationDegrees = 0.0f;
        float cameraControllerDistanceFromInterestPointMeters = 1781.0f;

        Eegeo::Space::EcefTangentBasis cameraInterestBasis;
        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(location.ToECEF(), cameraControllerOrientationDegrees, cameraInterestBasis);

        m_pGlobeCameraController->SetView(cameraInterestBasis, cameraControllerDistanceFromInterestPointMeters);

        m_pCameraTransitionController = Eegeo_NEW(ExampleApp::CameraTransitions::SdkModel::CameraTransitionController)(*m_pGlobeCameraController, *m_pNavigationService, terrainModelModule.GetTerrainHeightProvider());

        CreateApplicationModelModules();
        
        m_pLoadingScreen = CreateLoadingScreen(screenProperties, m_pWorld->GetRenderingModule(), m_pWorld->GetPlatformAbstractionModule());
        
        m_pDebugStats = Eegeo_NEW(Eegeo::Debug::DebugStats)(&memoryStats,
                                                            GetCameraController(),
                                                            GetCameraController().GetRenderCamera(),
                                                            &(m_pWorld->GetFrameTimer()),
                                                            &(m_pWorld->GetStreamingModule().GetResourceNodeCache())
                                                            );
        
        m_pGlobeCameraJumpController = Eegeo_NEW(Eegeo::Camera::GlobeCamera::GlobeCameraJumpController)(GetCameraController());
       
        m_pCommandServerModule = Eegeo::Debug::DebugServer::CommandServerModule::BuildDefault();
        
        m_pFrustumVolumeProvider = Eegeo_NEW(FrustumVolumeProvider)(m_pWorld->GetStreamingModule().GetStreamingVolumeController(), GetCameraController());
        
        m_pStubRouteCreator = Eegeo_NEW(StubRouteCreator);
        
        m_pPerformanceTestRunner = Eegeo_NEW(Eegeo::Debug::Profile::PerformanceTestRunner)(
                                                                                           m_pWorld->GetMapDebugModule().GetDebugCameraSplinePlaybackService(),
                                                                                           *m_pDebugStats);
        
        m_pDefaultCommandsModule = Eegeo_NEW(Eegeo::Debug::DebugServer::DefaultCommandsModule)(
                                            *m_pWorld,
                                            *m_pDebugStats,
                                            GetCameraController().GetGlobeCameraController(),
                                            *m_pGlobeCameraJumpController,
                                            *m_pFrustumVolumeProvider,
                                            *m_pStubRouteCreator,
                                            *m_pPerformanceTestRunner,
                                            m_pCommandServerModule->GetCommandRegistry());

        m_pStreamingVolume = Eegeo_NEW(Eegeo::Streaming::CameraFrustumStreamingVolume)(mapModule.GetResourceCeilingProvider(),
                             Eegeo::Config::LodRefinementConfig::GetLodRefinementAltitudesForDeviceSpec(platformConfig.PerformanceConfig.DeviceSpecification),
                             Eegeo::Streaming::QuadTreeCube::MAX_DEPTH_TO_VISIT,
                             mapModule.GetEnvironmentFlatteningService());

    }

    MobileExampleApp::~MobileExampleApp()
    {
        Eegeo_DELETE m_pStreamingVolume;

        DestroyApplicationModelModules();

        Eegeo_DELETE m_pDefaultCommandsModule;
        Eegeo_DELETE m_pFrustumVolumeProvider;
        Eegeo_DELETE m_pStubRouteCreator;
        Eegeo_DELETE m_pCommandServerModule;
        Eegeo_DELETE m_pGlobeCameraJumpController;
        Eegeo_DELETE m_pDebugStats;
        
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

        m_pReactionControllerModule = Eegeo_NEW(Reaction::View::ReactionControllerModule)();

        m_pAboutPageModule = Eegeo_NEW(ExampleApp::AboutPage::View::AboutPageModule)(m_identityProvider,
                                                                                     m_pReactionControllerModule->GetReactionControllerModel());
        
        m_pOptionsModule = Eegeo_NEW(ExampleApp::Options::OptionsModule)(m_identityProvider,
                                                                         m_pReactionControllerModule->GetReactionControllerModel(),
                                                                         m_messageBus,
                                                                         m_networkCapabilities);

        m_pSearchModule = Eegeo_NEW(Search::SdkModel::SearchModule)(DecartaApiKey,
                          m_platformAbstractions.GetWebLoadRequestFactory(),
                          m_platformAbstractions.GetUrlEncoder(),
                          *m_pGlobeCameraController,
                          *m_pCameraTransitionController,
                          m_messageBus);

        m_pCompassModule = Eegeo_NEW(ExampleApp::Compass::SdkModel::CompassModule)(*m_pNavigationService,
                           *m_pGlobeCameraController,
                           m_identityProvider,
                           m_messageBus);
        
        m_pGpsMarkerModule = Eegeo_NEW(ExampleApp::GpsMarker::SdkModel::GpsMarkerModule)(m_pWorld->GetRenderingModule(),
                                                                                         m_platformAbstractions,
                                                                                         m_pWorld->GetLocationService(),
                                                                                         m_pWorld->GetTerrainModelModule(),
                                                                                         m_messageBus);

        Eegeo::Modules::Map::CityThemesModule& cityThemesModule = world.GetCityThemesModule();

        m_pWeatherMenuModule = Eegeo_NEW(ExampleApp::WeatherMenu::SdkModel::WeatherMenuModule)(m_platformAbstractions.GetFileIO(),
                               cityThemesModule.GetCityThemesService(),
                               cityThemesModule.GetCityThemesUpdater(),
                               m_messageBus);
        
        m_pPrimaryMenuModule = Eegeo_NEW(ExampleApp::PrimaryMenu::View::PrimaryMenuModule)(m_identityProvider,
                                                                                           AboutPageModule().GetAboutPageViewModel(),
                                                                                           OptionsModule().GetOptionsViewModel(),
                                                                                           m_pReactionControllerModule->GetReactionControllerModel());

        m_pSecondaryMenuModule = Eegeo_NEW(ExampleApp::SecondaryMenu::SdkModel::SecondaryMenuModule)(m_identityProvider,
                                 m_pReactionControllerModule->GetReactionControllerModel(),
                                 m_pSearchModule->GetSearchQueryPerformer(),
                                 m_messageBus);

        m_pPlaceJumpsModule = Eegeo_NEW(PlaceJumps::SdkModel::PlaceJumpsModule)(m_platformAbstractions.GetFileIO(),
                              GetCameraController(),
                              m_pCompassModule->GetCompassModel(),
                              m_pSecondaryMenuModule->GetSecondaryMenuViewModel(),
                              m_messageBus);

        m_pCategorySearchModule = Eegeo_NEW(ExampleApp::CategorySearch::SdkModel::CategorySearchModule(
                                                SearchModule().GetSearchQueryPerformer(),
                                                m_pSecondaryMenuModule->GetSecondaryMenuViewModel(),
                                                m_messageBus));

        m_pSecondaryMenuModule->AddMenuSection("Search", "place", m_pCategorySearchModule->GetCategorySearchMenuModel(), true);
        m_pSecondaryMenuModule->AddMenuSection("Weather", "weather", m_pWeatherMenuModule->GetWeatherMenuModel(), true);
        m_pSecondaryMenuModule->AddMenuSection("Locations", "location", m_pPlaceJumpsModule->GetPlaceJumpsMenuModel(), true);

        Eegeo::Modules::Map::MapModule& mapModule = world.GetMapModule();

        m_pFlattenButtonModule = Eegeo_NEW(ExampleApp::FlattenButton::SdkModel::FlattenButtonModule)(mapModule.GetEnvironmentFlatteningService(),
                                 m_pWeatherMenuModule->GetWeatherController(),
                                 m_identityProvider,
                                 m_messageBus);

        InitialisePinsModules(mapModule, world);
        
        m_pMyPinsModule = Eegeo_NEW(ExampleApp::MyPins::SdkModel::MyPinsModule)(m_pWorldPinsModule->GetWorldPinsService(),
                                                                                m_platformAbstractions,
                                                                                m_persistentSettings,
                                                                                m_pPrimaryMenuModule->GetPrimaryMenuViewModel(),
                                                                                m_messageBus,
                                                                                *m_pCameraTransitionController);
        
        m_pSearchResultPoiModule = Eegeo_NEW(ExampleApp::SearchResultPoi::View::SearchResultPoiModule)(m_identityProvider,
                                                                                                       m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                                       m_pMyPinsModule->GetMyPinsService(),
                                                                                                       m_pMyPinsModule->GetMyPinsRepository(),
                                                                                                       m_pCategorySearchModule->GetSearchResultIconCategoryMapper(),
                                                                                                       m_messageBus);
        
        m_pSearchResultMenuModule = Eegeo_NEW(SearchResultMenu::SdkModel::SearchResultMenuModule)(m_pSearchModule->GetSearchResultRepository(),
                                                                                                  m_pSearchModule->GetSearchQueryPerformer(),
                                                                                                  m_identityProvider,
                                                                                                  *m_pCameraTransitionController,
                                                                                                  m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                                  m_messageBus);
        
        m_pSearchResultOnMapModule = Eegeo_NEW(SearchResultOnMap::SdkModel::SearchResultOnMapModule)(m_pSearchModule->GetSearchResultRepository(),
                                                                                                     m_pSearchResultPoiModule->GetSearchResultPoiViewModel(),
                                                                                                     m_pWorldPinsModule->GetWorldPinsService(),
                                                                                                     m_pMyPinsModule->GetMyPinsRepository(),
                                                                                                     m_pCategorySearchModule->GetSearchResultIconCategoryMapper(),
                                                                                                     m_messageBus);
        
        m_pPrimaryMenuModule->AddMenuSection("My Pins", "place", m_pMyPinsModule->GetMyPinsMenuModel(), true);

        m_pMyPinCreationModule = Eegeo_NEW(ExampleApp::MyPinCreation::SdkModel::MyPinCreationModule)(m_pMyPinsModule->GetMyPinsService(),
                                 m_identityProvider,
                                 m_pPrimaryMenuModule->GetPrimaryMenuViewModel(),
                                 m_pSecondaryMenuModule->GetSecondaryMenuViewModel(),
                                 m_pSearchModule->GetSearchQueryPerformer(),
                                 m_pSearchResultMenuModule->GetMenuViewModel(),
                                 m_pSearchModule->GetSearchRefreshService(),
                                 m_messageBus,
                                 m_pReactionControllerModule->GetReactionControllerModel());

        m_pPoiRingModule = Eegeo_NEW(ExampleApp::MyPinCreation::PoiRing::SdkModel::PoiRingModule)(m_pMyPinCreationModule->GetMyPinCreationModel(),
                           m_platformAbstractions,
                           m_pWorld->GetRenderingModule(),
                           m_pWorld->GetAsyncLoadersModule(),
                           m_pWorld->GetLightingModule(),
                           m_pWorld->GetTerrainModelModule(),
                           m_pWorld->GetMapModule());


        m_pMyPinCreationDetailsModule = Eegeo_NEW(ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsModule)(m_identityProvider,
                                        m_pReactionControllerModule->GetReactionControllerModel());

        m_pMyPinDetailsModule = Eegeo_NEW(ExampleApp::MyPinDetails::SdkModel::MyPinDetailsModule)(m_identityProvider,
                                                                                                  m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                                  m_pMyPinsModule->GetMyPinsService(),
                                                                                                  m_pSearchResultPoiModule->GetSearchResultPoiViewModel(),
                                                                                                  m_messageBus);

        m_pInitialExperienceDialogsModule = Eegeo_NEW(ExampleApp::InitialExperience::Dialogs::View::InitialExperienceDialogsModule)();

        std::vector<ScreenControl::View::IScreenControlViewModel*> reactors(GetReactorControls());
        std::vector<ExampleApp::OpenableControl::View::IOpenableControlViewModel*> openables(GetOpenableControls());

        m_pModalityModule = Eegeo_NEW(Modality::View::ModalityModule)(m_messageBus, openables);

        m_pReactionModelModule = Eegeo_NEW(Reaction::View::ReactionModelModule)(m_pReactionControllerModule->GetReactionControllerModel(),
                                 openables,
                                 reactors);

        Eegeo::Modules::Map::StreamingModule& streamingModule = world.GetStreamingModule();
        m_pWorldAreaLoaderModule = Eegeo_NEW(WorldAreaLoader::SdkModel::WorldAreaLoaderModule)(streamingModule.GetPrecachingService());

        m_initialExperienceModule.InitialiseWithApplicationModels(m_pWorldAreaLoaderModule->GetWorldAreaLoaderModel());
    }

    void MobileExampleApp::DestroyApplicationModelModules()
    {
    	Eegeo_DELETE m_pInitialExperienceDialogsModule;

        m_initialExperienceModule.TearDown();
        
        Eegeo_DELETE m_pWorldAreaLoaderModule;
        
        Eegeo_DELETE m_pReactionModelModule;
        
        Eegeo_DELETE m_pModalityModule;
        
        Eegeo_DELETE m_pMyPinDetailsModule;
        
        Eegeo_DELETE m_pMyPinCreationDetailsModule;
        
        Eegeo_DELETE m_pPoiRingModule;
        
        Eegeo_DELETE m_pMyPinCreationModule;

        Eegeo_DELETE m_pSearchResultMenuModule;

        Eegeo_DELETE m_pSearchResultOnMapModule;

        Eegeo_DELETE m_pSearchResultPoiModule;
        
        Eegeo_DELETE m_pMyPinsModule;

        Eegeo_DELETE m_pWorldPinsModule;

        Eegeo_DELETE m_pPinsModule;

        Eegeo_DELETE m_pPlaceJumpsModule;

        Eegeo_DELETE m_pCategorySearchModule;

        Eegeo_DELETE m_pSecondaryMenuModule;

        Eegeo_DELETE m_pPrimaryMenuModule;

        Eegeo_DELETE m_pFlattenButtonModule;

        Eegeo_DELETE m_pWeatherMenuModule;
        
        Eegeo_DELETE m_pGpsMarkerModule;

        Eegeo_DELETE m_pCompassModule;

        Eegeo_DELETE m_pSearchModule;

        Eegeo_DELETE m_pOptionsModule;
        
        Eegeo_DELETE m_pAboutPageModule;

        Eegeo_DELETE m_pReactionControllerModule;
    }

    std::vector<ExampleApp::OpenableControl::View::IOpenableControlViewModel*> MobileExampleApp::GetOpenableControls() const
    {
        std::vector<ExampleApp::OpenableControl::View::IOpenableControlViewModel*> openables;
        openables.push_back(&PrimaryMenuModule().GetPrimaryMenuViewModel());
        openables.push_back(&SecondaryMenuModule().GetSecondaryMenuViewModel());
        openables.push_back(&SearchResultMenuModule().GetMenuViewModel());
        openables.push_back(&SearchResultPoiModule().GetObservableOpenableControl());
        openables.push_back(&AboutPageModule().GetObservableOpenableControl());
        openables.push_back(&MyPinCreationDetailsModule().GetObservableOpenableControl());
        openables.push_back(&MyPinDetailsModule().GetObservableOpenableControl());
        openables.push_back(&MyPinCreationModule().GetObservableOpenableControl());
        openables.push_back(&OptionsModule().GetObservableOpenableControl());
        return openables;
    }

    std::vector<ExampleApp::ScreenControl::View::IScreenControlViewModel*> MobileExampleApp::GetReactorControls() const
    {
        std::vector<ExampleApp::ScreenControl::View::IScreenControlViewModel*> reactors;
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

        float spriteWidth = m_pinDiameter;
        float spriteHeight = m_pinDiameter;

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

        m_pWorldPinsModule = Eegeo_NEW(ExampleApp::WorldPins::SdkModel::WorldPinsModule)(
                                 m_pPinsModule->GetRepository(),
                                 m_pPinsModule->GetController(),
                                 mapModule.GetEnvironmentFlatteningService(),
                                 m_identityProvider,
                                 m_messageBus);
    }

    void MobileExampleApp::OnPause()
    {
        m_pCommandServerModule->GetTcpListener().StopListening();
        Eegeo::EegeoWorld& eegeoWorld = World();
        eegeoWorld.OnPause();
    }

    void MobileExampleApp::OnResume()
    {
        m_pCommandServerModule->GetTcpListener().StartListening(Eegeo::Debug::DebugServer::CommandServerModule::DefaultPort);
        
        Eegeo::EegeoWorld& eegeoWorld = World();
        eegeoWorld.OnResume();
    }

    void MobileExampleApp::Update(float dt)
    {
        Eegeo::EegeoWorld& eegeoWorld(World());
        
        m_pCommandServerModule->Update();

        eegeoWorld.EarlyUpdate(dt);

        m_pGlobeCameraController->Update(dt);
        m_pCameraTransitionController->Update(dt);

        Eegeo::Camera::CameraState cameraState(m_pGlobeCameraController->GetCameraState());
        Eegeo::Camera::RenderCamera renderCamera(m_pGlobeCameraController->GetRenderCamera());
        Eegeo::dv3 ecefInterestPoint(cameraState.InterestPointEcef());

        m_pPoiRingModule->GetPoiRingController().Update(dt, renderCamera, ecefInterestPoint);

        Eegeo::EegeoUpdateParameters updateParameters(dt,
                cameraState.LocationEcef(),
                cameraState.InterestPointEcef(),
                cameraState.ViewMatrix(),
                cameraState.ProjectionMatrix(),
                GetUpdatedStreamingVolume(cameraState, renderCamera),
                m_screenProperties);

        eegeoWorld.Update(updateParameters);

        m_pSearchModule->GetSearchRefreshService().TryRefreshSearch(dt, ecefInterestPoint);

        m_pPinsModule->GetController().Update(dt, renderCamera);

        if(!eegeoWorld.Initialising())
        {
            WorldPinsModule().GetWorldPinsScaleController().Update(dt, renderCamera);
            CompassModule().GetCompassUpdateController().Update(dt);
            CompassModule().GetCompassUpdateController().Update(dt);
            m_pGpsMarkerModule->GetGpsMarkerController().Update(dt, renderCamera);

            InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel = m_initialExperienceModule.GetInitialExperienceModel();
            if(!initialExperienceModel.HasCompletedInitialExperience())
            {
                InitialExperience::SdkModel::IInitialExperienceController& initialExperienceController = m_initialExperienceModule.GetInitialExperienceController();
                initialExperienceController.Update(dt);
            }
  
            if (!m_setFlurryLocation)
            {
                Eegeo::dv3 gpsLocation;
                if(m_pNavigationService->TryGetGpsLocationOnTerrain(gpsLocation))
                {
                    Eegeo::Space::LatLong ll = Eegeo::Space::LatLong::FromECEF(gpsLocation);
                    FLURRY_SET_POSITION(ll.GetLatitudeInDegrees(), ll.GetLongitudeInDegrees(), 0.f, 0.f);
                    m_setFlurryLocation = true;
                }
            }
        }

        m_pNavigationService->Update(dt);

        UpdateLoadingScreen(dt);
    }

    void MobileExampleApp::Draw (float dt)
    {
        Eegeo::EegeoWorld& eegeoWorld = World();

        Eegeo::Camera::CameraState cameraState(m_pGlobeCameraController->GetCameraState());
        Eegeo::Camera::RenderCamera renderCamera(m_pGlobeCameraController->GetRenderCamera());
        Eegeo::dv3 ecefInterestPoint(cameraState.InterestPointEcef());

        if(!eegeoWorld.Initialising())
        {
            WorldPinsModule().GetWorldPinsInFocusController().Update(dt, ecefInterestPoint, renderCamera);
        }

        Eegeo::EegeoDrawParameters drawParameters(cameraState.LocationEcef(),
                cameraState.InterestPointEcef(),
                cameraState.ViewMatrix(),
                cameraState.ProjectionMatrix(),
                m_screenProperties);

        eegeoWorld.Draw(drawParameters);

        if (m_pLoadingScreen != NULL)
        {
            m_pLoadingScreen->Draw();
        }
    }

    void MobileExampleApp::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
        m_screenProperties = screenProperties;

        if (m_pLoadingScreen != NULL)
        {
            m_pLoadingScreen->NotifyScreenDimensionsChanged(screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());
        }

        m_pGlobeCameraController->UpdateScreenProperties(m_screenProperties);
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
        }
    }

    bool MobileExampleApp::IsRunning() const
    {
        return !m_pWorld->Initialising();
    }

    Eegeo::Streaming::IStreamingVolume& MobileExampleApp::GetUpdatedStreamingVolume(const Eegeo::Camera::CameraState& cameraState,
            const Eegeo::Camera::RenderCamera& renderCamera)
    {
        std::vector<Eegeo::Geometry::Plane> frustumPlanes(Eegeo::Geometry::Frustum::PLANES_COUNT);
        BuildFrustumPlanesFromViewProjection(frustumPlanes, renderCamera.GetViewProjectionMatrix());
        const double d = renderCamera.GetAltitude() * Eegeo::Streaming::StreamingVolumeController::CAMERA_ALTITUDE_TO_FAR_PLANE_DISTANCE_MULTIPLIER;
        const double cameraFarPlaneD = fmin(fmax(d, Eegeo::Streaming::StreamingVolumeController::MIN_STREAMING_FAR_PLANE_DISTANCE),
                                            frustumPlanes[Eegeo::Geometry::Frustum::PLANE_FAR].d);
        frustumPlanes[Eegeo::Geometry::Frustum::PLANE_FAR].d = static_cast<float>(cameraFarPlaneD);

        m_pStreamingVolume->updateStreamingVolume(renderCamera.GetEcefLocation(), frustumPlanes, renderCamera.GetFOV());
        m_pStreamingVolume->ResetVolume(cameraState.InterestPointEcef());
        return *m_pStreamingVolume;
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
        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if(World().Initialising() || poiRingTouchController.IsDragging())
        {
            return;
        }

        m_pCameraTouchController->Event_TouchPan(data);
    }

    void MobileExampleApp::Event_TouchPan_Start(const AppInterface::PanData& data)
    {
        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if(World().Initialising() || poiRingTouchController.IsDragging())
        {
            return;
        }

        m_pCameraTouchController->Event_TouchPan_Start(data);
    }

    void MobileExampleApp::Event_TouchPan_End(const AppInterface::PanData& data)
    {
        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
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

        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if (!poiRingTouchController.HandleTouchDown(data, m_pGlobeCameraController->GetRenderCamera(), m_pGlobeCameraController->GetGlobeCameraController()))
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

        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if (!poiRingTouchController.HandleTouchMove(data, m_pGlobeCameraController->GetRenderCamera(), m_pGlobeCameraController->GetGlobeCameraController()))
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

        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if (!poiRingTouchController.HandleTouchUp(data))
        {
            m_pCameraTouchController->Event_TouchUp(data);
        }
    }
}
