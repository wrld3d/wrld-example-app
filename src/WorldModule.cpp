// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "WorldModule.h"
#include "EegeoWorld.h"
#include "ApplicationConfiguration.h"
#include "IIdentity.h"
#include "CameraFrustumStreamingVolume.h"
#include "LodRefinementConfig.h"
#include "QuadTreeCube.h"
#include "CityThemesModule.h"
#include "ILocationService.h"
#include "WebConnectivityValidator.h"
#include "TerrainHeightProvider.h"
#include "EnvironmentFlatteningService.h"
#include "ResourceCeilingProvider.h"
#include "AggregateCollisionBvhProvider.h"
#include "EnvironmentRayCaster.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "GlBufferPool.h"
#include "VertexLayoutPool.h"
#include "InteriorInteractionModel.h"
#include "ICityThemesService.h"
#include "ICityThemesUpdater.h"
#include "GlobalLighting.h"
#include "GlobalFogging.h"
#include "TerrainRayPicker.h"
#include "IRayPicker.h"
#include "CollisionMeshResourceRepository.h"
#include "InteriorTransitionModel.h"
#include "InteriorSelectionModel.h"
#include "PrecacheService.h"
#include "JpegLoader.h"
#include "IInteriorsLabelController.h"
#include "IImmutableInteriorViewModel.h"

namespace ExampleApp
{
    void WorldModule::Register(const TContainerBuilder& builder)
    {
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               Eegeo::Search::Service::SearchServiceCredentials* pSearchCredentials=NULL;
                                               return std::make_shared<Eegeo::EegeoWorld>(
                                                                                          context.resolve<ExampleApp::ApplicationConfig::ApplicationConfiguration>()->EegeoApiKey(),
                                                                                          *(context.resolve<Eegeo::Modules::IPlatformAbstractionModule>()),
                                                                                          *(context.resolve<Eegeo::Helpers::Jpeg::IJpegLoader>()),
                                                                                          *(context.resolve<Eegeo::Rendering::ScreenProperties>()),
                                                                                          *(context.resolve<Eegeo::Location::ILocationService>()),
                                                                                          *(context.resolve<Eegeo::UI::NativeUIFactories>()),
                                                                                          Eegeo::EnvironmentCharacterSet::JapanPlaceNames,
                                                                                          *(context.resolve<Eegeo::Config::PlatformConfig>()),
                                                                                          pSearchCredentials,
                                                                                          context.resolve<Eegeo::IEegeoErrorHandler>().get()
                                                                                          );
                                           }).singleInstance();
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                         {
                                             return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::Modules::IPlatformAbstractionModule>()->GetFileIO());
                                         }).singleInstance();
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                         {
                                             return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::Modules::IPlatformAbstractionModule>()->GetWorkPool());
                                         }).singleInstance();
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                         {
                                             return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetRenderingModule().GetRenderableFilters());
                                         }).singleInstance();
        builder->registerType<Eegeo::Helpers::IdentityProvider>().as<Eegeo::Helpers::IIdentityProvider>().singleInstance();
        builder->registerType<Eegeo::Helpers::Jpeg::JpegLoader>().as<Eegeo::Helpers::Jpeg::IJpegLoader>().singleInstance();

        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetWebConnectivityValidator());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetTerrainModelModule().GetTerrainHeightProvider());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetMapModule().GetEnvironmentFlatteningService());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetMapModule().GetResourceCeilingProvider());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetMapModule().GetAggregateCollisionBvhProvider());
                                           }).as<Eegeo::Collision::ICollisionBvhProvider>().singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return std::make_shared<Eegeo::Collision::EnvironmentRayCaster>(
                                                                                                               *(context.resolve<Eegeo::Collision::AggregateCollisionBvhProvider>()),
                                                                                                               *(context.resolve<Eegeo::Rendering::EnvironmentFlatteningService>()));
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return std::make_shared<Eegeo::Collision::EnvironmentRayCaster>(
                                                                                                               *(context.resolve<Eegeo::Collision::AggregateCollisionBvhProvider>()),
                                                                                                               *(context.resolve<Eegeo::Rendering::EnvironmentFlatteningService>()));
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               
                                               return std::make_shared<Eegeo::Streaming::CameraFrustumStreamingVolume>(*(context.resolve<Eegeo::Streaming::ResourceCeilingProvider>()),
                                                                                                                       Eegeo::Config::LodRefinementConfig::GetLodRefinementAltitudesForDeviceSpec(context.resolve<Eegeo::Config::PlatformConfig>()->PerformanceConfig.DeviceSpecification),
                                                                                                                       14,
                                                                                                                       *(context.resolve<Eegeo::Rendering::EnvironmentFlatteningService>()));
                                           }).singleInstance();
        
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetRenderingModule().GetShaderIdGenerator());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetRenderingModule().GetMaterialIdGenerator());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetRenderingModule().GetGlBufferPool());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetRenderingModule().GetVertexLayoutPool());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetRenderingModule().GetVertexBindingPool());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetMapModule().GetInteriorsPresentationModule().GetInteriorInteractionModel());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                         {
                                             return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetMapModule().GetInteriorsPresentationModule().GetInteriorViewModel());
                                         }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                         {
                                             return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetMapModule().GetInteriorsPresentationModule().GetInteriorSelectionModel());
                                         }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                         {
                                             return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetMapModule().GetInteriorsPresentationModule().GetInteriorTransitionModel());
                                         }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                         {
                                             return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetMapModule().GetInteriorsPresentationModule().GetInteriorsLabelsController());
                                         }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetCityThemesModule().GetCityThemesService());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetCityThemesModule().GetCityThemesUpdater());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetLightingModule().GetGlobalFogging());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetLightingModule().GetGlobalLighting());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetRenderingModule());
                                           }).singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                           {
                                               Eegeo::EegeoWorld& world = *(context.resolve<Eegeo::EegeoWorld>());
                                               return std::make_shared<Eegeo::Resources::Terrain::Collision::TerrainRayPicker>(world.GetTerrainModelModule().GetTerrainHeightProvider(),
                                                                                                                               world.GetTerrainModelModule().GetCollisionMeshResourceRepository());
                                           }).as<Eegeo::Collision::IRayPicker>().singleInstance();
        
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                         {
                                             return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::EegeoWorld>()->GetStreamingModule().GetPrecachingService());
                                         }).singleInstance();
    }
}
