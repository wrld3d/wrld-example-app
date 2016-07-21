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
#include "GlobeCameraControllerFactory.h"
#include "GlobeCameraTouchSettings.h"
#include "GlobeCameraController.h"
#include "GpsGlobeCameraComponentConfiguration.h"
#include "InteriorsCameraController.h"
#include "InteriorsCameraControllerFactory.h"
#include "ITextureFileLoader.h"
#include "IWeatherMenuModule.h"
#include "SettingsMenuModule.h"
#include "SearchMenuModule.h"
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
#include "IPoiRingTouchController.h"
#include "MyPinCreationModule.h"
#include "SearchResultSectionModule.h"
#include "PoiRingModule.h"
#include "IPoiRingController.h"
#include "MyPinCreationDetailsModule.h"
#include "MyPinsModule.h"
#include "IWorldPinsInFocusController.h"
#include "IWorldPinsScaleController.h"
#include "IWorldPinsFloorHeightController.h"
#include "MyPinDetailsModule.h"
#include "QuadTreeCube.h"
#include "LodRefinementConfig.h"
#include "StreamingVolumeController.h"
#include "GpsMarkerModule.h"
#include "IGpsMarkerController.h"
#include "INetworkCapabilities.h"
#include "ISearchServiceModule.h"
#include "IMyPinsService.h"
#include "IEegeoErrorHandler.h"
#include "OptionsMenuOption.h"
#include "AboutPageMenuOption.h"
#include "ImagePathHelpers.h"
#include "WatermarkModule.h"
#include "InteriorsPresentationModule.h"
#include "InteriorsModelModule.h"
#include "InteriorsExplorerModule.h"
#include "InteriorsEntitiesPinsModule.h"
#include "InteriorsEntitiesPinsController.h"
#include "PinsModule.h"
#include "MapModeModule.h"
#include "AppModeModel.h"
#include "ToursModule.h"
#include "IToursCameraController.h"
#include "IToursCameraTransitionController.h"
#include "ToursCameraState.h"
#include "ExampleTourStateMachineFactory.h"
#include "ICompassViewModel.h"
#include "CombinedSearchServiceModule.h"
#include "GeoNamesSearchServiceModule.h"
#include "EegeoSearchServiceModule.h"
#include "SearchVendorNames.h"
#include "YelpSearchConstants.h"
#include "YelpSearchServiceModule.h"
#include "AppCameraModule.h"
#include "AppCameraController.h"
#include "AppModeStatesFactory.h"
#include "AppGlobeCameraWrapper.h"
#include "AppInteriorCameraWrapper.h"
#include "NativeUIFactories.h"
#include "UserInteractionModule.h"
#include "UserInteractionModel.h"
#include "EnvironmentFlatteningService.h"
#include "TwitterFeedModule.h"
#include "ITwitterFeedService.h"
#include "TwitterFeedTourModule.h"
#include "SceneModelsModule.h"
#include "VisualMapModule.h"
#include "ConnectivityChangedObserver.h"
#include "SurveyModule.h"
#include "SurveyObserver.h"
#include "InteriorsResourceCounts.h"
#include "HttpAsyncTextureLoader.h"
#include "HttpAsyncCubeTextureLoader.h"
#include "InteriorsMaterialsModule.h"
#include "IInteriorsTextureResourceService.h"
#include "InteriorMaterialSemantics.h"
#include "IInteriorsMaterialDtoRepository.h"
#include "InteriorsMaterialDto.h"
#include "InteriorsMaterialParser.h"
#include "InteriorsMaterialDescriptorLoader.h"
#include "InteriorsNavigationService.h"
#include "ModalityIgnoredReactionModel.h"
#include "ReactorIgnoredReactionModel.h"
#include "WorldPinIconMappingFactory.h"

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
            loadingScreenConfig.screenOversampleScaling = screenProperties.GetOversampleScale();
            loadingScreenConfig.loadingBarOffset = Eegeo::v2(0.5f, 0.1f);

            Eegeo::Rendering::LoadingScreen* loadingScreen = Eegeo::Rendering::LoadingScreen::Create(
            			Helpers::ImageHelpers::GetImageNameForDevice("SplashScreen", ".png"),
                        loadingScreenConfig,
                        renderingModule.GetShaderIdGenerator(),
                        renderingModule.GetMaterialIdGenerator(),
                        renderingModule.GetGlBufferPool(),
                        renderingModule.GetVertexLayoutPool(),
                        renderingModule.GetVertexBindingPool(),
                        platformAbstractionModule.GetTextureFileLoader());
            return loadingScreen;
        }

        void AddLocalMaterials(
                Eegeo::Helpers::IFileIO& fileIO,
                Eegeo::Resources::Interiors::IInteriorsTextureResourceService& interiorsTextureResourceService,
                Eegeo::Resources::Interiors::Materials::IInteriorsMaterialDtoRepository& interiorsMaterialDtoRepository)
        {
            std::fstream stream;
            size_t size;

            if(fileIO.OpenFile(stream, size, "Interiors/Custom/custom_material_definitions.json"))
            {
                std::string materialsJson((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

                rapidjson::Document document;
                if (document.Parse<0>(materialsJson.c_str()).HasParseError())
                {
                    Eegeo_ASSERT(false, "Error parsing local materials JSON file.\n");
                }

                for (rapidjson::Value::ConstMemberIterator iter = document.MemberBegin();
                     iter != document.MemberEnd();
                     ++iter)
                {
                    std::string interiorName(iter->name.GetString());
                    const rapidjson::Value& materials(iter->value);

                    size_t materialsCount(materials.Size());
                    for(size_t i = 0; i < materialsCount; ++ i)
                    {
                        const rapidjson::Value& materialJson(materials[static_cast<int>(i)]);
                        Eegeo::Resources::Interiors::Materials::InteriorsMaterialDto dto(Eegeo::Resources::Interiors::Materials::ParseMaterial(materialJson));
                        Eegeo_ASSERT(!interiorsMaterialDtoRepository.Contains(interiorName, dto.materialName));
                        interiorsMaterialDtoRepository.Add(interiorName, dto);

                        const bool localTexture = true;
                        Eegeo::Resources::Interiors::Materials::CreateAndRegisterTextures(dto, interiorsTextureResourceService, localTexture);
                        Eegeo::Resources::Interiors::Materials::CreateAndRegisterCubeMapTextures(dto, interiorsTextureResourceService, localTexture);
                    }
                }
            }
        }
    }

    MobileExampleApp::MobileExampleApp(
        const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
        Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
        Eegeo::Rendering::ScreenProperties& screenProperties,
        Eegeo::Location::ILocationService& locationService,
        Eegeo::UI::NativeUIFactories& nativeUIFactories,
        Eegeo::Config::PlatformConfig platformConfig,
        Eegeo::Helpers::Jpeg::IJpegLoader& jpegLoader,
        ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule& initialExperienceModule,
        ExampleApp::PersistentSettings::IPersistentSettingsModel& persistentSettings,
        ExampleAppMessaging::TMessageBus& messageBus,
        ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
        Net::SdkModel::INetworkCapabilities& networkCapabilities,
        ExampleApp::Metrics::IMetricsService& metricsService,        
        Eegeo::IEegeoErrorHandler& errorHandler,
        Menu::View::IMenuReactionModel& menuReaction)
        : m_pGlobeCameraController(NULL)
        , m_pCameraTouchController(NULL)
        , m_pCurrentTouchController(NULL)
        , m_pNavigationService(NULL)
        , m_pInteriorsNavigationService(NULL)
        , m_pWorld(NULL)
        , m_platformAbstractions(platformAbstractions, networkCapabilities)
        , m_pLoadingScreen(NULL)
        , m_pinDiameter(28.f)
        , m_initialisedApplicationViewState(false)
        , m_pCameraTransitionController(NULL)
        , m_pSettingsMenuModule(NULL)
        , m_pSearchMenuModule(NULL)
        , m_pSearchResultSectionModule(NULL)
        , m_pModalityModule(NULL)
        , m_pCategorySearchModule(NULL)
        , m_pMapModeModule(NULL)
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
        , m_messageBus(messageBus)
        , m_sdkDomainEventBus(sdkModelDomainEventBus)
        , m_persistentSettings(persistentSettings)
        , m_pMyPinCreationModule(NULL)
        , m_pPoiRingModule(NULL)
        , m_pMyPinCreationDetailsModule(NULL)
        , m_pMyPinsModule(NULL)
        , m_pMyPinDetailsModule(NULL)
        , m_pOptionsModule(NULL)
        , m_pWatermarkModule(NULL)
        , m_pInteriorsExplorerModule(NULL)
        , m_pInteriorsEntitiesPinsModule(NULL)
        , m_screenProperties(screenProperties)
        , m_networkCapabilities(networkCapabilities)
        , m_setMetricsLocation(false)
        , m_pSearchServiceModule(NULL)
        , m_metricsService(metricsService)
        , m_applicationConfiguration(applicationConfiguration)
        , m_interiorsEnabled(platformConfig.OptionsConfig.EnableInteriors)
        , m_pToursModule(NULL)
        , m_pGlobeCameraWrapper(NULL)
        , m_pTwitterFeedModule(NULL)
        , m_pTwitterFeedTourModule(NULL)
        , m_pVisualMapModule(NULL)
        , m_pSurveyModule(NULL)
        , m_pConnectivityChangedObserver(NULL)
        , m_toursPinDiameter(48.f)
        , m_enableTours(false)
        , m_menuReaction(menuReaction)
        , m_pModalityIgnoredReactionModel(NULL)
        , m_pReactorIgnoredReactionModel(NULL)
    {
        m_metricsService.BeginSession(m_applicationConfiguration.FlurryAppKey(), EEGEO_PLATFORM_VERSION_NUMBER);

        m_pWorld = Eegeo_NEW(Eegeo::EegeoWorld)(applicationConfiguration.EegeoApiKey(),
                                                m_platformAbstractions,
                                                jpegLoader,
                                                screenProperties,
                                                locationService,
                                                nativeUIFactories,
                                                Eegeo::EnvironmentCharacterSet::JapanPlaceNames,
                                                platformConfig,
                                                NULL,
                                                &errorHandler
                                                );

        AddLocalMaterials(m_platformAbstractions.GetFileIO(),
                          m_pWorld->GetMapModule().GetInteriorsMaterialsModule().GetInteriorsTextureResourceService(),
                          m_pWorld->GetMapModule().GetInteriorsMaterialsModule().GetInteriorsMaterialDtoRepository());

        m_pConnectivityChangedObserver = Eegeo_NEW(Net::SdkModel::ConnectivityChangedObserver)(m_pWorld->GetWebConnectivityValidator(), messageBus);

        Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = m_pWorld->GetTerrainModelModule();
        Eegeo::Modules::Map::MapModule& mapModule = m_pWorld->GetMapModule();

        m_pNavigationService = Eegeo_NEW(Eegeo::Location::NavigationService)(&m_pWorld->GetLocationService(),
                               &terrainModelModule.GetTerrainHeightProvider());

        Eegeo::Camera::GlobeCamera::GpsGlobeCameraControllerFactory cameraControllerFactory(terrainModelModule.GetTerrainHeightProvider(),
                mapModule.GetEnvironmentFlatteningService(),
                mapModule.GetResourceCeilingProvider(),
                *m_pNavigationService);

        m_pAppModeModel = Eegeo_NEW(AppModes::SdkModel::AppModeModel)(m_messageBus);

        const bool useLowSpecSettings = false;

        Eegeo::Camera::GlobeCamera::GpsGlobeCameraComponentConfiguration gpsGlobeCameraConfig = Eegeo::Camera::GlobeCamera::GpsGlobeCameraComponentConfiguration::CreateDefault();
        gpsGlobeCameraConfig.panToUnlockThreshold =  0.03f;
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchControllerConfig = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
        Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration globeCameraConfig = Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration::CreateDefault(useLowSpecSettings);

        m_pGlobeCameraController = cameraControllerFactory.Create(gpsGlobeCameraConfig, touchControllerConfig, globeCameraConfig, m_screenProperties);
        
        m_pGlobeCameraWrapper = Eegeo_NEW(AppCamera::SdkModel::AppGlobeCameraWrapper)(*m_pGlobeCameraController);

        m_pCameraTouchController = &m_pGlobeCameraController->GetTouchController();

        Eegeo::Camera::GlobeCamera::GlobeCameraTouchSettings touchSettings = m_pGlobeCameraController->GetGlobeCameraController().GetTouchSettings();
        touchSettings.TiltEnabled = true;
        m_pGlobeCameraController->GetGlobeCameraController().SetTouchSettings(touchSettings);

        Eegeo::Space::LatLongAltitude location = m_applicationConfiguration.InterestLocation();
        float cameraControllerOrientationDegrees = m_applicationConfiguration.OrientationDegrees();
        float cameraControllerDistanceFromInterestPointMeters = m_applicationConfiguration.DistanceToInterestMetres();

        Eegeo::Space::EcefTangentBasis cameraInterestBasis;
        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(location.ToECEF(), cameraControllerOrientationDegrees, cameraInterestBasis);

        m_pGlobeCameraController->SetView(cameraInterestBasis, cameraControllerDistanceFromInterestPointMeters);
        
        
        Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();

        m_pCameraTransitionService = Eegeo_NEW(ExampleApp::CameraTransitions::SdkModel::CameraTransitionService)();

        m_pStreamingVolume = Eegeo_NEW(Eegeo::Streaming::CameraFrustumStreamingVolume)(mapModule.GetResourceCeilingProvider(),
                                                                                       Eegeo::Config::LodRefinementConfig::GetLodRefinementAltitudesForDeviceSpec(platformConfig.PerformanceConfig.DeviceSpecification),
                                                                                       Eegeo::Streaming::QuadTreeCube::MAX_DEPTH_TO_VISIT,
                                                                                       mapModule.GetEnvironmentFlatteningService());
        
        CreateApplicationModelModules(nativeUIFactories, platformConfig.OptionsConfig.InteriorsAffectedByFlattening);
        
        m_pCameraTransitionController = Eegeo_NEW(ExampleApp::CameraTransitions::SdkModel::CameraTransitionController)(*m_pGlobeCameraController,
                                                                                                                       m_pInteriorsExplorerModule->GetInteriorsCameraController(),
                                                                                                                       *m_pNavigationService,
                                                                                                                       *m_pInteriorsNavigationService,
                                                                                                                       terrainModelModule.GetTerrainHeightProvider(),
                                                                                                                       *m_pAppModeModel,
                                                                                                                       m_pAppCameraModule->GetController(),
                                                                                                                       interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                                                                       interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                                                       interiorsPresentationModule.GetInteriorTransitionModel(),
                                                                                                                       m_pInteriorsExplorerModule->GetInteriorsExplorerModel(),
                                                                                                                       m_messageBus);
        m_pCameraTransitionService->SetTransitionController(*m_pCameraTransitionController);
        
        m_pLoadingScreen = CreateLoadingScreen(screenProperties, m_pWorld->GetRenderingModule(), m_pWorld->GetPlatformAbstractionModule());
        
        if(m_applicationConfiguration.TryStartAtGpsLocation())
        {
            m_pNavigationService->SetGpsMode(Eegeo::Location::NavigationService::GpsModeFollow);
        }
        
        InitialiseAppState(nativeUIFactories);
        
        m_pUserInteractionModule = Eegeo_NEW(UserInteraction::SdkModel::UserInteractionModule)(m_pAppCameraModule->GetController(), *m_pCameraTransitionService, m_pInteriorsExplorerModule->GetInteriorsExplorerUserInteractionModel(), m_messageBus);
    }

    MobileExampleApp::~MobileExampleApp()
    {
        OnPause();

		m_pAppModeModel->DestroyStateMachine();

        Eegeo_DELETE m_pUserInteractionModule;
        
        Eegeo_DELETE m_pStreamingVolume;

        DestroyApplicationModelModules();

        Eegeo_DELETE m_pCameraTransitionService;
        Eegeo_DELETE m_pCameraTransitionController;
        Eegeo_DELETE m_pNavigationService;
        Eegeo_DELETE m_pGlobeCameraWrapper;
        Eegeo_DELETE m_pGlobeCameraController;
        Eegeo_DELETE m_pLoadingScreen;

        Eegeo_DELETE m_pAppModeModel;

        Eegeo_DELETE m_pConnectivityChangedObserver;
        
        Eegeo_DELETE m_pWorld;
    }

    void MobileExampleApp::CreateApplicationModelModules(Eegeo::UI::NativeUIFactories& nativeUIFactories,
                                                         const bool interiorsAffectedByFlattening)
    {
        Eegeo::EegeoWorld& world = *m_pWorld;
        
        m_pReactorIgnoredReactionModel = Eegeo_NEW(Menu::View::ReactorIgnoredReactionModel)();
        m_pModalityIgnoredReactionModel = Eegeo_NEW(Menu::View::ModalityIgnoredReactionModel)();
        
        m_pReactionControllerModule = Eegeo_NEW(Reaction::View::ReactionControllerModule)(*m_pReactorIgnoredReactionModel);

        m_pAboutPageModule = Eegeo_NEW(ExampleApp::AboutPage::View::AboutPageModule)(m_identityProvider,
                                                                                     m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                     m_applicationConfiguration.ProductVersion());
        
        m_pOptionsModule = Eegeo_NEW(ExampleApp::Options::OptionsModule)(m_identityProvider,
                                                                         m_pReactionControllerModule->GetReactionControllerModel(),
                                                                         m_messageBus,
                                                                         m_networkCapabilities);

        const bool useGeoName = true;
        if(useGeoName)
        {
            m_searchServiceModules[Search::GeoNamesVendorName] = Eegeo_NEW(Search::GeoNames::SdkModel::GeoNamesSearchServiceModule)(m_platformAbstractions.GetWebLoadRequestFactory(),
                                                                                                                                    m_platformAbstractions.GetUrlEncoder(),
                                                                                                                                    m_networkCapabilities,
                                                                                                                                    m_applicationConfiguration.GeoNamesUserName());
        }
        const bool useEegeoPois = true;
        if(useEegeoPois)
        {
            std::vector<std::string> supportedCategories = Search::Yelp::SearchConstants::GetCategories();
            m_searchServiceModules[Search::EegeoVendorName] = Eegeo_NEW(Search::EegeoPois::SdkModel::EegeoSearchServiceModule)(m_platformAbstractions.GetWebLoadRequestFactory(),
                                                                                                                               m_platformAbstractions.GetUrlEncoder(),
                                                                                                                               m_networkCapabilities,
                                                                                                                               supportedCategories,
                                                                                                                               m_applicationConfiguration.EegeoSearchServiceUrl(),
                                                                                                                               m_applicationConfiguration.EegeoApiKey(),
                                                                                                                               world.GetMapModule().GetInteriorsPresentationModule().GetInteriorInteractionModel()
                                                                                                                               );
        }
		
		const bool useYelpSearch = true;
        if (useYelpSearch)
        {
            m_searchServiceModules[ExampleApp::Search::YelpVendorName] = Eegeo_NEW(ExampleApp::Search::Yelp::YelpSearchServiceModule)(
                m_platformAbstractions.GetWebLoadRequestFactory(),
                m_networkCapabilities,
                m_platformAbstractions.GetUrlEncoder(),
                m_applicationConfiguration.YelpConsumerKey(),
                m_applicationConfiguration.YelpConsumerSecret(),
                m_applicationConfiguration.YelpOAuthToken(),
                m_applicationConfiguration.YelpOAuthTokenSecret(),
                m_platformAbstractions.GetFileIO()
                );
        }
        
        m_pSearchServiceModule = Eegeo_NEW(Search::Combined::SdkModel::CombinedSearchServiceModule)(m_searchServiceModules, m_pWorld->GetMapModule().GetInteriorsPresentationModule().GetInteriorInteractionModel());
        
        m_pSearchModule = Eegeo_NEW(Search::SdkModel::SearchModule)(m_pSearchServiceModule->GetSearchService(),
                                                                    *m_pGlobeCameraController,
                                                                    *m_pCameraTransitionService,
                                                                    m_pWorld->GetMapModule().GetInteriorsPresentationModule().GetInteriorInteractionModel(),
                                                                    m_messageBus,
                                                                    m_sdkDomainEventBus);
        
        // TODO: Check if this module is still relevant
        m_pAppCameraModule = Eegeo_NEW(AppCamera::SdkModel::AppCameraModule)();
        
        m_pGpsMarkerModule = Eegeo_NEW(ExampleApp::GpsMarker::SdkModel::GpsMarkerModule)(m_pWorld->GetRenderingModule(),
                                                                                         m_platformAbstractions,
                                                                                         m_pWorld->GetLocationService(),
                                                                                         m_pWorld->GetTerrainModelModule(),
                                                                                         m_pWorld->GetMapModule(),
                                                                                         m_messageBus);

        Eegeo::Modules::Map::CityThemesModule& cityThemesModule = world.GetCityThemesModule();
        
        Eegeo::Modules::Map::MapModule& mapModule = world.GetMapModule();
        
        m_pVisualMapModule = Eegeo_NEW(VisualMap::SdkModel::VisualMapModule)(cityThemesModule.GetCityThemesService(),
                                                                             cityThemesModule.GetCityThemesUpdater(),
                                                                             mapModule.GetEnvironmentFlatteningService());
        
        m_pSurveyModule = Eegeo_NEW(Surveys::SdkModel::SurveyModule)(m_messageBus,
                                                                     m_persistentSettings);
        
        m_pSurveyModule->GetSurveyObserver().OnStartup();

        m_pWeatherMenuModule = Eegeo_NEW(ExampleApp::WeatherMenu::SdkModel::WeatherMenuModule)(m_platformAbstractions.GetFileIO(),
                                                                                               m_pVisualMapModule->GetVisualMapService(),
                                                                                               m_messageBus,
                                                                                               m_metricsService,
                                                                                               *m_pAppModeModel);
        
        m_pSettingsMenuModule = Eegeo_NEW(ExampleApp::SettingsMenu::SdkModel::SettingsMenuModule)(m_identityProvider,
                                                                                                  m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                                  m_pAboutPageModule->GetAboutPageViewModel(),
                                                                                                  m_pOptionsModule->GetOptionsViewModel(),
                                                                                                  m_pWeatherMenuModule->GetWeatherMenuModel());
        
        m_pPlaceJumpsModule = Eegeo_NEW(PlaceJumps::SdkModel::PlaceJumpsModule)(m_platformAbstractions.GetFileIO(),
                              CameraTransitionController(),
                              m_pSettingsMenuModule->GetSettingsMenuViewModel(),
                              m_messageBus,
                              m_metricsService,
                              m_menuReaction);

        m_pCategorySearchModule = Eegeo_NEW(ExampleApp::CategorySearch::SdkModel::CategorySearchModule(
                                                m_pSearchServiceModule->GetCategorySearchModels(),
                                                SearchModule().GetSearchQueryPerformer(),
                                                m_pSettingsMenuModule->GetSettingsMenuViewModel(),
                                                m_messageBus,
                                                m_metricsService,
                                                m_menuReaction));

        m_pMapModeModule = Eegeo_NEW(MapMode::SdkModel::MapModeModule)(m_pVisualMapModule->GetVisualMapService());

        m_pFlattenButtonModule = Eegeo_NEW(ExampleApp::FlattenButton::SdkModel::FlattenButtonModule)(m_pMapModeModule->GetMapModeModel(),
                                 m_identityProvider,
                                 m_messageBus);
    

        InitialisePinsModules(mapModule, world, interiorsAffectedByFlattening, m_screenProperties.GetOversampleScale());
        
        m_pMyPinsModule = Eegeo_NEW(ExampleApp::MyPins::SdkModel::MyPinsModule)(m_pWorldPinsModule->GetWorldPinsService(),
                                                                                m_platformAbstractions,
                                                                                m_persistentSettings,
                                                                                m_pSettingsMenuModule->GetSettingsMenuViewModel(),
                                                                                m_messageBus,
                                                                                m_sdkDomainEventBus,
                                                                                *m_pCameraTransitionService,
                                                                                m_pSearchModule->GetMyPinsSearchResultRefreshService(),
                                                                                m_metricsService,
                                                                                "",
                                                                                "",
                                                                                m_menuReaction,
                                                                                *m_pModalityIgnoredReactionModel);
        
        m_pSearchResultPoiModule = Eegeo_NEW(ExampleApp::SearchResultPoi::View::SearchResultPoiModule)(m_identityProvider,
                                                                                                       m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                                       m_pMyPinsModule->GetMyPinsService(),
                                                                                                       m_pSearchModule->GetSearchResultMyPinsService(),
                                                                                                       m_pCategorySearchModule->GetSearchResultIconCategoryMapper(),
                                                                                                       world.GetPlatformAbstractionModule().GetWebLoadRequestFactory(),
                                                                                                       m_messageBus);
        
        m_pSearchMenuModule = Eegeo_NEW(ExampleApp::SearchMenu::SdkModel::SearchMenuModule)(m_identityProvider,
                                                                                            m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                            m_pSearchModule->GetSearchQueryPerformer(),
                                                                                            m_messageBus,
                                                                                            m_metricsService);
        
        Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();
        Eegeo::Modules::Map::Layers::InteriorsModelModule& interiorsModelModule = mapModule.GetInteriorsModelModule();

        m_pSearchResultSectionModule = Eegeo_NEW(SearchResultSection::SdkModel::SearchResultSectionModule)(m_pSearchMenuModule->GetSearchMenuViewModel(),
                                                                                                           m_pSearchModule->GetSearchResultRepository(),
                                                                                                           m_pSearchModule->GetSearchQueryPerformer(),
                                                                                                           *m_pCameraTransitionService,
                                                                                                           interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                                           interiorsModelModule.GetInteriorMarkerModelRepository(),
                                                                                                           m_pAppCameraModule->GetController(),
                                                                                                           m_messageBus);
        
        m_pSearchResultOnMapModule = Eegeo_NEW(SearchResultOnMap::SdkModel::SearchResultOnMapModule)(m_pSearchModule->GetSearchResultRepository(),
                                                                                                     m_pSearchResultPoiModule->GetSearchResultPoiViewModel(),
                                                                                                     m_pWorldPinsModule->GetWorldPinsService(),
                                                                                                     m_pMyPinsModule->GetMyPinsService(),
                                                                                                     m_pCategorySearchModule->GetSearchResultIconCategoryMapper(),
                                                                                                     m_pSearchModule->GetSearchResultMyPinsService(),
                                                                                                     m_messageBus,
                                                                                                     m_metricsService,
                                                                                                     m_menuReaction);
        

        Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory cameraControllerFactory(m_pWorld->GetTerrainModelModule().GetTerrainHeightProvider(),
                                                                                         mapModule.GetEnvironmentFlatteningService(),
                                                                                         mapModule.GetResourceCeilingProvider());
        
        const Eegeo::Resources::Interiors::InteriorsCameraConfiguration& interiorsCameraConfig(Eegeo::Resources::Interiors::InteriorsCameraController::CreateDefaultConfig());
        const Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration& globeCameraConfig = Eegeo::Resources::Interiors::InteriorsCameraControllerFactory::DefaultGlobeCameraControllerConfiguration();
        const Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration& globeCameraTouchConfig = Eegeo::Resources::Interiors::InteriorsCameraControllerFactory::DefaultGlobeCameraTouchControllerConfiguration();
        
        
        const Eegeo::Resources::Interiors::InteriorsCameraControllerFactory interiorsCameraControllerFactory(
                                                                                                       interiorsCameraConfig,
                                                                                                       globeCameraConfig,
                                                                                                       globeCameraTouchConfig,
                                                                                                       cameraControllerFactory,
                                                                                                       m_screenProperties,
                                                                                                       interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                                       interiorsPresentationModule.GetInteriorViewModel(),
                                                                                                       mapModule.GetEnvironmentFlatteningService(),
                                                                                                       interiorsAffectedByFlattening );
        
        
        Eegeo::Modules::Map::StreamingModule& streamingModule = world.GetStreamingModule();
        m_pWorldAreaLoaderModule = Eegeo_NEW(WorldAreaLoader::SdkModel::WorldAreaLoaderModule)(streamingModule.GetPrecachingService());
        
        m_initialExperienceModule.InitialiseWithApplicationModels(m_pWorldAreaLoaderModule->GetWorldAreaLoaderModel());
        
        const InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel = m_initialExperienceModule.GetInitialExperienceModel();
        
        m_pInteriorsExplorerModule = Eegeo_NEW(InteriorsExplorer::SdkModel::InteriorsExplorerModule)(interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                                     interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                                                     interiorsPresentationModule.GetInteriorTransitionModel(),
                                                                                                     interiorsModelModule.GetInteriorMarkerModelRepository(),
                                                                                                     m_pWorldPinsModule->GetWorldPinsService(),
                                                                                                     m_pWorldPinsModule->GetWorldPinsScaleController(),
                                                                                                     mapModule.GetEnvironmentFlatteningService(),
                                                                                                     m_pVisualMapModule->GetVisualMapService(),
                                                                                                     interiorsCameraControllerFactory,
                                                                                                     m_screenProperties,
                                                                                                     m_identityProvider,
                                                                                                     m_messageBus,
                                                                                                     m_metricsService,
                                                                                                     initialExperienceModel,
                                                                                                     interiorsAffectedByFlattening);
        
        m_pMyPinCreationModule = Eegeo_NEW(ExampleApp::MyPinCreation::SdkModel::MyPinCreationModule)(m_pMyPinsModule->GetMyPinsService(),
                                                                                                     m_identityProvider,
                                                                                                     m_pSettingsMenuModule->GetSettingsMenuViewModel(),
                                                                                                     m_pSearchModule->GetSearchQueryPerformer(),
                                                                                                     m_pSearchMenuModule->GetSearchMenuViewModel(),
                                                                                                     m_pSearchModule->GetSearchRefreshService(),
                                                                                                     m_pInteriorsExplorerModule->GetScreenControlViewModel(),
                                                                                                     m_messageBus,
                                                                                                     m_pReactionControllerModule->GetReactionControllerModel());
        
        m_pPoiRingModule = Eegeo_NEW(ExampleApp::MyPinCreation::PoiRing::SdkModel::PoiRingModule)(m_pMyPinCreationModule->GetMyPinCreationModel(),
                                                                                                  m_platformAbstractions,
                                                                                                  m_pWorld->GetRenderingModule(),
                                                                                                  m_pWorld->GetAsyncLoadersModule(),
                                                                                                  m_pWorld->GetLightingModule(),
                                                                                                  m_pWorld->GetTerrainModelModule(),
                                                                                                  m_pWorld->GetMapModule(),
                                                                                                  *m_pAppModeModel,
                                                                                                  m_screenProperties,
                                                                                                  interiorsAffectedByFlattening);
        
        m_pMyPinCreationDetailsModule = Eegeo_NEW(ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsModule)(m_identityProvider,
                                                                                                                      m_pReactionControllerModule->GetReactionControllerModel());
        
        m_pMyPinDetailsModule = Eegeo_NEW(ExampleApp::MyPinDetails::SdkModel::MyPinDetailsModule)(m_identityProvider,
                                                                                                  m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                                  m_pMyPinsModule->GetMyPinsService(),
                                                                                                  m_pSearchResultPoiModule->GetSearchResultPoiViewModel(),
                                                                                                  m_messageBus,
                                                                                                  m_menuReaction);
        
        m_pInteriorsNavigationService = Eegeo_NEW(ExampleApp::InteriorsNavigation::SdkModel::InteriorsNavigationService)(world.GetLocationService(),
                                                                                                                         m_pInteriorsExplorerModule->GetInteriorsCameraController(),
                                                                                                                         m_pInteriorsExplorerModule->GetTouchController(),
                                                                                                                         interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                                                                         interiorsPresentationModule.GetInteriorInteractionModel());
        
        
        m_pCompassModule = Eegeo_NEW(ExampleApp::Compass::SdkModel::CompassModule)(*m_pNavigationService,
                                                                                   *m_pInteriorsNavigationService,
                                                                                   world.GetLocationService(),
                                                                                   m_pAppCameraModule->GetController(),
                                                                                   m_identityProvider,
                                                                                   m_messageBus,
                                                                                   m_metricsService,
                                                                                   m_pInteriorsExplorerModule->GetInteriorsExplorerModel(),
                                                                                   *m_pAppModeModel,
                                                                                   m_pWorld->GetNativeUIFactories().AlertBoxFactory());

        m_pInteriorCameraWrapper = Eegeo_NEW(AppCamera::SdkModel::AppInteriorCameraWrapper)(m_pInteriorsExplorerModule->GetInteriorsCameraController());

        m_pWatermarkModule = Eegeo_NEW(ExampleApp::Watermark::SdkModel::WatermarkModule)(m_identityProvider,
                                                                                         m_applicationConfiguration.Name(),
                                                                                         m_applicationConfiguration.GoogleAnalyticsReferrerToken(),
                                                                                         world.GetMapModule().GetInteriorsPresentationModule().GetInteriorSelectionModel(),
                                                                                         world.GetMapModule().GetInteriorsModelModule().GetInteriorsModelRepository(),
                                                                                         m_pInteriorsExplorerModule->GetInteriorsExplorerModel(),
                                                                                         m_messageBus);
        
        InitialiseToursModules(mapModule, world, interiorsAffectedByFlattening);
        
        m_pTwitterFeedModule = Eegeo_NEW(Social::TwitterFeed::TwitterFeedModule)(m_applicationConfiguration.TwitterAuthCode(),
                                                                                 World().GetPlatformAbstractionModule().GetWebLoadRequestFactory());
        
        if (m_interiorsEnabled)
        {
            m_pInteriorsEntitiesPinsModule = Eegeo_NEW(InteriorsEntitiesPins::SdkModel::InteriorsEntitiesPinsModule(m_pWorld->GetPlatformAbstractionModule(),
                                                                                                                m_pWorld->GetRenderingModule(),
                                                                                                                m_pWorld->GetMapModule(),
                                                                                                                m_screenProperties));
                                                                                                            
        }
        
        std::vector<ScreenControl::View::IScreenControlViewModel*> reactors(GetReactorControls());
        std::vector<ExampleApp::OpenableControl::View::IOpenableControlViewModel*> openables(GetOpenableControls());

        m_pModalityModule = Eegeo_NEW(Modality::View::ModalityModule)(m_messageBus, openables, *m_pModalityIgnoredReactionModel);

        m_pReactionModelModule = Eegeo_NEW(Reaction::View::ReactionModelModule)(m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                openables,
                                                                                reactors,
                                                                                *m_pReactorIgnoredReactionModel);
        
        m_pSearchMenuModule->SetSearchSection("Search Results", m_pSearchResultSectionModule->GetSearchResultSectionModel());
        m_pSearchMenuModule->AddMenuSection("Find", m_pCategorySearchModule->GetCategorySearchMenuModel(), true);
        m_pSearchMenuModule->AddMenuSection("Locations", m_pPlaceJumpsModule->GetPlaceJumpsMenuModel(), true);
        m_pSearchMenuModule->AddMenuSection("My Pins", m_pMyPinsModule->GetMyPinsMenuModel(), true);
    }
    
    void MobileExampleApp::InitialiseAppState(Eegeo::UI::NativeUIFactories& nativeUIFactories)
    {
        Eegeo::Modules::Map::MapModule& mapModule = m_pWorld->GetMapModule();
        Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();
        
        AppModes::States::SdkModel::AppModeStatesFactory appModeStatesFactory(m_pAppCameraModule->GetController(),
                                                                              *m_pGlobeCameraWrapper,
                                                                              *m_pInteriorCameraWrapper,
                                                                              m_pToursModule->GetCameraController(),
                                                                              *m_pStreamingVolume,
                                                                              m_pInteriorsExplorerModule->GetInteriorVisibilityUpdater(),
                                                                              m_pInteriorsExplorerModule->GetInteriorsExplorerModel(),
                                                                              m_pInteriorsExplorerModule->GetInteriorsExplorerUserInteractionModel(),
                                                                              *m_pAppModeModel,
                                                                              m_pToursModule->GetTourService(),
                                                                              interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                              interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                              nativeUIFactories,
                                                                              m_pMyPinCreationModule->GetMyPinCreationModel(),
                                                                              m_pVisualMapModule->GetVisualMapService());
        
        m_pAppModeModel->InitialiseStateMachine(appModeStatesFactory.CreateStateMachineStates());
    }

    void MobileExampleApp::DestroyApplicationModelModules()
    {
        m_initialExperienceModule.TearDown();
        
        Eegeo_DELETE m_pModalityIgnoredReactionModel;
        
        Eegeo_DELETE m_pReactorIgnoredReactionModel;
        
        Eegeo_DELETE m_pTwitterFeedModule;

        Eegeo_DELETE m_pToursModule;
        
        Eegeo_DELETE m_pTwitterFeedTourModule;
        
        Eegeo_DELETE m_pWorldAreaLoaderModule;
        
        Eegeo_DELETE m_pReactionModelModule;
        
        Eegeo_DELETE m_pModalityModule;
        
        Eegeo_DELETE m_pCompassModule;
        
        Eegeo_DELETE m_pInteriorsNavigationService;;
        
        Eegeo_DELETE m_pMyPinDetailsModule;
        
        Eegeo_DELETE m_pMyPinCreationDetailsModule;
        
        Eegeo_DELETE m_pPoiRingModule;
        
        Eegeo_DELETE m_pMyPinCreationModule;
        
        Eegeo_DELETE m_pSearchMenuModule;

        Eegeo_DELETE m_pSearchResultSectionModule;

        Eegeo_DELETE m_pSearchResultOnMapModule;

        Eegeo_DELETE m_pSearchResultPoiModule;
        
        Eegeo_DELETE m_pPlaceJumpsModule;

		Eegeo_DELETE m_pFlattenButtonModule;

        Eegeo_DELETE m_pMapModeModule;

        Eegeo_DELETE m_pCategorySearchModule;
        
        Eegeo_DELETE m_pSettingsMenuModule;
        
        Eegeo_DELETE m_pSurveyModule;

        Eegeo_DELETE m_pVisualMapModule;
        
        Eegeo_DELETE m_pWeatherMenuModule;
        
        Eegeo_DELETE m_pGpsMarkerModule;
        
        Eegeo_DELETE m_pInteriorCameraWrapper;

        Eegeo_DELETE m_pWatermarkModule;
        
		Eegeo_DELETE m_pInteriorsExplorerModule;

        Eegeo_DELETE m_pSearchModule;
        
        for(std::map<std::string, ExampleApp::Search::SdkModel::ISearchServiceModule*>::iterator it = m_searchServiceModules.begin(); it != m_searchServiceModules.end(); ++it)
        {
            Eegeo_DELETE (*it).second;
        }
        m_searchServiceModules.clear();

		Eegeo_DELETE m_pMyPinsModule;

		Eegeo_DELETE m_pWorldPinsModule;

		Eegeo_DELETE m_pPinsModule;

        Eegeo_DELETE m_pAppCameraModule;
        
        Eegeo_DELETE m_pOptionsModule;
        
        Eegeo_DELETE m_pAboutPageModule;
        

        Eegeo_DELETE m_pReactionControllerModule;
    }

    std::vector<ExampleApp::OpenableControl::View::IOpenableControlViewModel*> MobileExampleApp::GetOpenableControls() const
    {
        std::vector<ExampleApp::OpenableControl::View::IOpenableControlViewModel*> openables;
        openables.push_back(&SettingsMenuModule().GetSettingsMenuViewModel());
        openables.push_back(&SearchMenuModule().GetSearchMenuViewModel());
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
        reactors.push_back(&SettingsMenuModule().GetSettingsMenuViewModel());
        reactors.push_back(&SearchMenuModule().GetSearchMenuViewModel());
        reactors.push_back(&FlattenButtonModule().GetScreenControlViewModel());
        reactors.push_back(&WorldPinsModule().GetScreenControlViewModel());
        reactors.push_back(&CompassModule().GetScreenControlViewModel());
        reactors.push_back(&MyPinCreationModule().GetInitiationScreenControlViewModel());
        reactors.push_back(&WatermarkModule().GetScreenControlViewModel());
        reactors.push_back(&InteriorsExplorerModule().GetScreenControlViewModel());
        if(m_enableTours)
        {
            reactors.push_back(&ToursModule().GetToursExplorerViewModel());
        }
        return reactors;
    }
    
    Eegeo::Pins::PinsModule* MobileExampleApp::CreatePlatformPinsModuleInstance(Eegeo::Modules::Map::MapModule& mapModule,
                                                                                Eegeo::EegeoWorld& world,
                                                                                const std::string& pinsTexture,
                                                                                float pinDiameter,
                                                                                int sheetSize)
    {
        m_platformAbstractions.GetTextureFileLoader().LoadTexture(m_pinIconsTexture,
                                                                  Helpers::ImageHelpers::GetImageNameForDevice(pinsTexture, ".png"),
                                                                  false);
        Eegeo_ASSERT(m_pinIconsTexture.textureId != 0);
        
        int numberOfTilesAlongEachAxisOfTexturePage = sheetSize;
        m_pPinIconsTexturePageLayout = Eegeo_NEW(Eegeo::Rendering::RegularTexturePageLayout)(numberOfTilesAlongEachAxisOfTexturePage);
        
        float spriteWidth = pinDiameter;
        float spriteHeight = pinDiameter;
        
        Eegeo::Modules::Core::RenderingModule& renderingModule = world.GetRenderingModule();
        Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = world.GetTerrainModelModule();
        
        return Eegeo_NEW(Eegeo::Pins::PinsModule)(
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
                                                  Eegeo::Rendering::LayerIds::InteriorEntities,
                                                  mapModule.GetEnvironmentFlatteningService(),
                                                  m_screenProperties,
                                                  false
                                                  );
    }
    
    void MobileExampleApp::InitialisePinsModules(Eegeo::Modules::Map::MapModule& mapModule,
                                                 Eegeo::EegeoWorld& world,
                                                 const bool interiorsAffectedByFlattening,
                                                 const float screenOversampleScale)
    {
        const int iconsPerRowColum = 10;

        m_pPinsModule = CreatePlatformPinsModuleInstance(mapModule, world, "SearchResultOnMap/pin_icon_texture_page", m_pinDiameter, iconsPerRowColum);
        
        Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();
        
        ExampleApp::WorldPins::SdkModel::WorldPinIconMappingFactory worldPinIconMappingFactory(m_platformAbstractions.GetFileIO(), "SearchResultOnMap/pin_sheet.json");
        
        m_pWorldPinsModule = Eegeo_NEW(ExampleApp::WorldPins::SdkModel::WorldPinsModule)(
                                 m_pPinsModule->GetRepository(),
                                 m_pPinsModule->GetController(),
                                 mapModule.GetEnvironmentFlatteningService(),
                                 m_identityProvider,
                                 m_messageBus,
                                 interiorsPresentationModule.GetInteriorInteractionModel(),
                                 interiorsPresentationModule.GetInteriorTransitionModel(),
                                 m_sdkDomainEventBus,
                                 interiorsAffectedByFlattening,
                                 m_menuReaction,
                                 screenOversampleScale,
                                 worldPinIconMappingFactory);
    }
    
    void MobileExampleApp::InitialiseToursModules(Eegeo::Modules::Map::MapModule& mapModule, Eegeo::EegeoWorld& world, const bool interiorsAffectedByFlattening)
    {
        m_pToursModule = Eegeo_NEW(ExampleApp::Tours::ToursModule)(m_identityProvider,
                                                                   m_metricsService,
                                                                   m_messageBus,
                                                                   WorldPinsModule().GetWorldPinsService(),
                                                                   SearchModule().GetSearchRefreshService(),
                                                                   SearchMenuModule().GetSearchMenuViewModel(),
                                                                   SettingsMenuModule().GetSettingsMenuViewModel(),
                                                                   WatermarkModule().GetScreenControlViewModel(),
                                                                   world.GetMapModule().GetResourceCeilingProvider(),
                                                                   m_screenProperties,
                                                                   *m_pGlobeCameraController,
                                                                   world.GetTerrainModelModule().GetTerrainHeightProvider(),
                                                                   m_sdkDomainEventBus,
                                                                   *m_pAppModeModel);
        
    }
    
    void MobileExampleApp::AddTours()
    {
        
        // Example tour.
        std::vector<Tours::SdkModel::TourStateModel> tourStates;
        tourStates.push_back(Tours::SdkModel::TourStateModel("Example place 1",
                                                             "Some example text",
                                                             "Tours/page",
                                                             "tours"));
        
        tourStates.push_back(Tours::SdkModel::TourStateModel("Example place 2",
                                                             "More example text",
                                                             "Tours/page",
                                                             "tours"));
        
        tourStates.push_back(Tours::SdkModel::TourStateModel("Example place 3",
                                                             "Some more example text",
                                                             "Tours/page",
                                                             "tours"));
        const std::string tourPinIconKey = "tour_entry";
        ExampleApp::Tours::SdkModel::TourModel tourModel("Example",
                                                         "Take the tour",
                                                         tourPinIconKey,
                                                         Eegeo::Space::LatLong::FromDegrees(37.784783, -122.402659),
                                                         true,
                                                         false,
                                                         ExampleApp::WorldPins::SdkModel::WorldPinInteriorData(),
                                                         false,
                                                         Helpers::ColorHelpers::Color::FromRGB(30, 123, 195),
                                                         Helpers::ColorHelpers::Color::FromRGB(255, 255, 255),
                                                         Helpers::ColorHelpers::Color::FromRGB(30, 123, 195),
                                                         Helpers::ColorHelpers::Color::FromRGB(30, 123, 195),
                                                         tourStates);
        
        
        Eegeo::Modules::Map::MapModule& mapModule = m_pWorld->GetMapModule();
        Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();
        
        Tours::SdkModel::TourInstances::Example::ExampleTourStateMachineFactory factory(ToursModule().GetCameraTransitionController(),
                                                                                        m_pWorldPinsModule->GetWorldPinsService(),
                                                                                        m_interiorsEnabled,
                                                                                        m_pInteriorsExplorerModule->GetInteriorVisibilityUpdater(),
                                                                                        interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                        interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                                        m_messageBus);
        
        ToursModule().GetTourService().AddTour(tourModel, *factory.CreateTourStateMachine(tourModel));
        
        m_pTwitterFeedTourModule = Eegeo_NEW(Tours::SdkModel::TourInstances::TwitterFeed::TwitterFeedTourModule)(ToursModule().GetCameraTransitionController(),
                                                                                                                 ToursModule().GetTourService(),
                                                                                                                 WorldPinsModule().GetWorldPinsService(),
                                                                                                                 m_pInteriorsExplorerModule->GetInteriorVisibilityUpdater(),
                                                                                                                 interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                                                 interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                                                                 ToursModule().GetTourRepository(),
                                                                                                                 TwitterFeedModule().GetTwitterFeedService(),
                                                                                                                 m_messageBus);
        
        const std::map<std::string, Tours::SdkModel::TourInstances::TwitterFeed::TweetStateData>& tweetStateDataMap = TwitterFeedTourModule().GetTweetStateDataMap();
        
        std::vector<std::string> twitterAccountNames;
        
        for(std::map<std::string, Tours::SdkModel::TourInstances::TwitterFeed::TweetStateData>::const_iterator it = tweetStateDataMap.begin(); it != tweetStateDataMap.end(); ++it)
        {
            twitterAccountNames.push_back((*it).first);
        }
        
        TwitterFeedModule().GetTwitterFeedService().LoadTimeLines(twitterAccountNames);
        
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
        
        m_pCurrentTouchController = &m_pAppCameraModule->GetController().GetTouchController();

        eegeoWorld.EarlyUpdate(dt);

        m_pCameraTransitionService->Update(dt);
        m_pAppCameraModule->GetController().Update(dt);
        
        m_pAppModeModel->Update(dt);
        
        if(ToursEnabled())
        {
            if(IsTourCameraActive())
            {
                ToursModule().GetCameraTransitionController().Update(dt);
            }
        }
        
        m_pInteriorsExplorerModule->Update(dt);
        
        Eegeo::Camera::RenderCamera renderCamera = m_pAppCameraModule->GetController().GetRenderCamera();
        Eegeo::Camera::CameraState cameraState = m_pAppCameraModule->GetController().GetCameraState();
        
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

        m_pSearchModule->GetSearchRefreshService().TryRefreshSearch(dt, ecefInterestPoint, cameraState.LocationEcef());

        m_pPinsModule->GetController().Update(dt, renderCamera);
        
        if(!eegeoWorld.Initialising() || (m_pLoadingScreen == NULL && eegeoWorld.Initialising()))
        {
            WorldPinsModule().GetWorldPinsService().Update(dt);
            WorldPinsModule().GetWorldPinsScaleController().Update(dt, renderCamera);
            WorldPinsModule().GetWorldPinsFloorHeightController().Update(dt);
            
            CompassModule().GetCompassUpdateController().Update(dt);
            CompassModule().GetCompassUpdateController().Update(dt);
            m_pGpsMarkerModule->GetGpsMarkerController().Update(dt, renderCamera);
            
            if (m_interiorsEnabled)
            {
                Eegeo_ASSERT(m_pInteriorsEntitiesPinsModule != NULL);
                
                m_pInteriorsEntitiesPinsModule->GetPinsModule().Update(dt, renderCamera);
                m_pInteriorsEntitiesPinsModule->GetInteriorsEntitiesPinsController().Update(dt);
            }
            
            InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel = m_initialExperienceModule.GetInitialExperienceModel();
            if(!initialExperienceModel.HasCompletedInitialExperience() && IsLoadingScreenComplete())
            {
                InitialExperience::SdkModel::IInitialExperienceController& initialExperienceController = m_initialExperienceModule.GetInitialExperienceController();
                initialExperienceController.Update(dt);
            }
  
            if (!m_setMetricsLocation)
            {
                Eegeo::dv3 gpsLocation;
                if(m_pNavigationService->TryGetGpsLocationOnTerrain(gpsLocation))
                {
                    Eegeo::Space::LatLong ll = Eegeo::Space::LatLong::FromECEF(gpsLocation);
                    m_metricsService.SetPosition(ll.GetLatitudeInDegrees(), ll.GetLongitudeInDegrees(), 0.f, 0.f);
                    m_setMetricsLocation = true;
                }
            }
        }

        m_pNavigationService->Update(dt);
        m_pInteriorsNavigationService->Update(dt);
        
        if(ToursEnabled())
        {
            ToursModule().GetTourService().UpdateCurrentTour(dt);
        }
        
        UpdateLoadingScreen(dt);
    }

    void MobileExampleApp::Draw (float dt)
    {
        Eegeo::EegeoWorld& eegeoWorld = World();

        Eegeo::Camera::RenderCamera renderCamera = m_pAppCameraModule->GetController().GetRenderCamera();
        Eegeo::Camera::CameraState cameraState = m_pAppCameraModule->GetController().GetCameraState();
        
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

		m_pPinsModule->UpdateScreenProperties(m_screenProperties);

        m_pGlobeCameraController->UpdateScreenProperties(m_screenProperties);

		m_pInteriorsExplorerModule->GetInteriorsCameraController().UpdateScreenProperties(m_screenProperties);
    }

    void MobileExampleApp::InitialiseApplicationViewState()
    {
        Eegeo_ASSERT(m_initialisedApplicationViewState == false, "Can only initialise application state once!\n");

        m_initialisedApplicationViewState = true;
        
        m_pSettingsMenuModule->GetSettingsMenuViewModel().AddToScreen();
        m_pSearchMenuModule->GetSearchMenuViewModel().AddToScreen();
        m_pFlattenButtonModule->GetScreenControlViewModel().AddToScreen();
        m_pCompassModule->GetScreenControlViewModel().AddToScreen();
        m_pMyPinCreationModule->GetInitiationScreenControlViewModel().AddToScreen();
        m_pWatermarkModule->GetWatermarkViewModel().AddToScreen();
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
            
            MyPinsModule().GetMyPinsService().LoadAllPinsFromDisk();
            
            if(ToursEnabled())
            {
                AddTours();
            }
        }
    }
    
    const bool MobileExampleApp::IsTourCameraActive() const
    {
        return ToursEnabled() ? ToursModule().GetTourService().IsTourActive() ||
                                !ToursModule().GetCameraTransitionController().IsTransitionComplete() : false;
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
        if (!CanAcceptTouch())
        {
            return;
        }

        m_pCurrentTouchController->Event_TouchRotate(data);
        
    }

    void MobileExampleApp::Event_TouchRotate_Start(const AppInterface::RotateData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }

        m_pCurrentTouchController->Event_TouchRotate_Start(data);
    }

    void MobileExampleApp::Event_TouchRotate_End(const AppInterface::RotateData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }

        m_pCurrentTouchController->Event_TouchRotate_End(data);
    }

    void MobileExampleApp::Event_TouchPinch(const AppInterface::PinchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }

        m_pCurrentTouchController->Event_TouchPinch(data);
    }

    void MobileExampleApp::Event_TouchPinch_Start(const AppInterface::PinchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }

        m_pCurrentTouchController->Event_TouchPinch_Start(data);
    }

    void MobileExampleApp::Event_TouchPinch_End(const AppInterface::PinchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }

        m_pCurrentTouchController->Event_TouchPinch_End(data);
    }

    void MobileExampleApp::Event_TouchPan(const AppInterface::PanData& data)
    {
        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if(!CanAcceptTouch() || poiRingTouchController.IsDragging())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_TouchPan(data);
    }

    void MobileExampleApp::Event_TouchPan_Start(const AppInterface::PanData& data)
    {
        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if(!CanAcceptTouch() || poiRingTouchController.IsDragging())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_TouchPan_Start(data);
    }

    void MobileExampleApp::Event_TouchPan_End(const AppInterface::PanData& data)
    {
        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if(!CanAcceptTouch() || poiRingTouchController.IsDragging())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_TouchPan_End(data);
    }

    void MobileExampleApp::Event_TouchTap(const AppInterface::TapData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        if(m_pWorldPinsModule->GetWorldPinsService().HandleTouchTap(data.point))
        {
            return;
        }
        
        m_pCurrentTouchController->Event_TouchTap(data);
    }

    void MobileExampleApp::Event_TouchDoubleTap(const AppInterface::TapData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }

		if (m_pWorldPinsModule->GetWorldPinsService().HandleTouchDoubleTap(data.point))
		{
			return;
		}

        m_pCurrentTouchController->Event_TouchDoubleTap(data);
    }

    void MobileExampleApp::Event_TouchDown(const AppInterface::TouchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }

        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if (!poiRingTouchController.HandleTouchDown(data, m_pAppCameraModule->GetController().GetRenderCamera(), m_pAppCameraModule->GetController().GetNonFlattenedCameraPosition()))
        {
            m_pCurrentTouchController->Event_TouchDown(data);
        }
    }

    void MobileExampleApp::Event_TouchMove(const AppInterface::TouchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if (!poiRingTouchController.HandleTouchMove(data, m_pAppCameraModule->GetController().GetRenderCamera(), m_pAppCameraModule->GetController().GetNonFlattenedCameraPosition()))
        {
            m_pCurrentTouchController->Event_TouchMove(data);
        }
    }

    void MobileExampleApp::Event_TouchUp(const AppInterface::TouchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }

        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if (!poiRingTouchController.HandleTouchUp(data))
        {
            m_pCurrentTouchController->Event_TouchUp(data);
        }
    }

    void MobileExampleApp::Event_Zoom(const AppInterface::ZoomData& data)
    {
		if (!CanAcceptTouch())
		{
			return;
		}

        m_pCurrentTouchController->Event_Zoom(data);
    }

    void MobileExampleApp::Event_Keyboard(const AppInterface::KeyboardData& data)
    {
        if (data.printable)
            Eegeo_TTY("Key Down: %c", data.keyCode);
        else
            Eegeo_TTY("Key Up: %c", data.keyCode);
    }

    void MobileExampleApp::Event_TiltStart(const AppInterface::TiltData& data)
    {
		if (!CanAcceptTouch())
		{
			return;
		}

        m_pCurrentTouchController->Event_TiltStart(data);
    }

    void MobileExampleApp::Event_TiltEnd(const AppInterface::TiltData& data)
    {
		if (!CanAcceptTouch())
		{
			return;
		}

        m_pCurrentTouchController->Event_TiltEnd(data);
    }

    void MobileExampleApp::Event_Tilt(const AppInterface::TiltData& data)
    {
		if (!CanAcceptTouch())
		{
			return;
		}

        m_pCurrentTouchController->Event_Tilt(data);
    }
    
    bool MobileExampleApp::CanAcceptTouch() const
    {
        const bool worldIsInitialising = World().Initialising() && m_pLoadingScreen != NULL;
        const bool userInteractionEnabled = m_pUserInteractionModule->GetUserInteractionModel().IsEnabled();
        
        InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel = m_initialExperienceModule.GetInitialExperienceModel();
        const bool lockedCameraStepsCompleted = initialExperienceModel.LockedCameraStepsCompleted();
        
        return !worldIsInitialising && lockedCameraStepsCompleted && userInteractionEnabled;
    }
}
