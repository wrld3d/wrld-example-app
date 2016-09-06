// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsModule.h"
#include "WorldPins.h"
#include "WorldPinsFactory.h"
#include "WorldPinsRepository.h"
#include "WorldPinsService.h"
#include "WorldPinsScaleController.h"
#include "WorldPinsFloorHeightController.h"
#include "WorldPinsInFocusController.h"
#include "WorldPinInFocusViewModel.h"
#include "WorldPinIconMappingFactory.h"
#include "WorldPinIconMapping.h"
#include "WorldPinInFocusObserver.h"
#include "WorldPinsModalityObserver.h"
#include "PinsModule.h"
#include "EegeoWorld.h"
#include "IFileIO.h"
#include "InteriorInteractionModel.h"
#include "InteriorTransitionModel.h"
#include "WorldPinOnMapController.h"
#include "IWorldPinOnMapView.h"
#include "IModalityModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            void WorldPinsModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<WorldPinsFactory>().as<IWorldPinsFactory>().singleInstance();
                builder->registerType<WorldPinsRepository>().as<IWorldPinsRepository>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     ExampleApp::WorldPins::SdkModel::WorldPinIconMappingFactory worldPinIconMappingFactory(
                                                                                                                                            *(context.resolve<Eegeo::Helpers::IFileIO>()),
                                                                                                                                            "SearchResultOnMap/pin_sheet.json",
                                                                                                                                            *(context.resolve<Eegeo::Helpers::ITextureFileLoader>()));
                                                     
                                                     return std::shared_ptr<ExampleApp::WorldPins::SdkModel::IWorldPinIconMapping>(worldPinIconMappingFactory.Create());
                                                 }).singleInstance();
                
                builder->registerType<WorldPinsService>().as<IWorldPinsService>().singleInstance();
                builder->registerType<WorldPinsScaleController>().as<IWorldPinsScaleController>().singleInstance();
                builder->registerType<WorldPinsFloorHeightController>().as<IWorldPinsFloorHeightController>().singleInstance();
                builder->registerType<View::WorldPinInFocusViewModel>().as<View::IWorldPinInFocusViewModel>().singleInstance();
                builder->registerType<WorldPinsInFocusController>().as<IWorldPinsInFocusController>().singleInstance();
                builder->registerType<View::WorldPinInFocusObserver>().singleInstance();
                builder->registerType<WorldPinsModalityObserver>().singleInstance();
                builder->registerType<View::WorldPinOnMapController>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto worldpinIconMapping = context.resolve<ExampleApp::WorldPins::SdkModel::IWorldPinIconMapping>();
                                                     auto world = context.resolve<Eegeo::EegeoWorld>();
                                                     return std::shared_ptr<Eegeo::Pins::PinsModule>(Eegeo::Pins::PinsModule::CreateWithAtlas(
                                                                                                    world->GetRenderingModule(),
                                                                                                    *(context.resolve<Eegeo::Modules::IPlatformAbstractionModule>()),
                                                                                                    world->GetMapModule(),
                                                                                                    worldpinIconMapping->GetTextureInfo().textureId,
                                                                                                    worldpinIconMapping->GetTexturePageLayout(),
                                                                                                    Eegeo::Rendering::LayerIds::InteriorEntities,
                                                                                                    *(context.resolve<Eegeo::Rendering::ScreenProperties>())));
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto pinsModule = context.resolve<Eegeo::Pins::PinsModule>();
                                                     return std::shared_ptr<Eegeo::Pins::PinRepository>(&pinsModule->GetRepository());
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto pinsModule = context.resolve<Eegeo::Pins::PinsModule>();
                                                     return std::shared_ptr<Eegeo::Pins::PinController>(&pinsModule->GetController());
                                                 }).singleInstance();
            }
            
            void WorldPinsModule::RegisterLeaves()
            {
                RegisterLeaf<WorldPinsModalityObserver>();
                RegisterLeaf<View::WorldPinInFocusObserver>();
                RegisterLeaf<View::WorldPinOnMapController>();
            }
        }
    }
}
