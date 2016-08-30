// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsEntitiesPinsModule.h"
#include "InteriorsEntitiesPinsController.h"

#include "IPlatformAbstractionModule.h"
#include "RenderingModule.h"
#include "MapModule.h"
#include "TerrainModelModule.h"
#include "InteriorsModelModule.h"
#include "InteriorsPresentationModule.h"

#include "RegularTexturePageLayout.h"

#include "PinsModule.h"
#include "ITextureFileLoader.h"
#include "InteriorsLabelController.h"
#include "ImagePathHelpers.h"
#include "IWorldPinIconMapping.h"
#include "EegeoWorld.h"
#include "InteriorInteractionModel.h"
#include "InteriorTransitionModel.h"

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            void InteriorsEntitiesPinsModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       auto world = context.resolve<Eegeo::EegeoWorld>();
                                                       auto worldPinMapping = context.resolve<WorldPins::SdkModel::IWorldPinIconMapping>();
                                                       auto module = Eegeo::Pins::PinsModule::CreateWithAtlas(world->GetRenderingModule(),
                                                                                                              *(context.resolve<Eegeo::Modules::IPlatformAbstractionModule>()),
                                                                                                              world->GetMapModule(),
                                                                                                              worldPinMapping->GetTextureInfo().textureId,
                                                                                                              worldPinMapping->GetTexturePageLayout(),
                                                                                                              Eegeo::Rendering::LayerIds::AfterWorld,
                                                                                                              *(context.resolve<Eegeo::Rendering::ScreenProperties>()));
                                                       return std::shared_ptr<Eegeo::Pins::PinsModule>(module);
                                                   }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::Pins::PinsModule>()->GetController());
                                                   }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::Pins::PinsModule>()->GetRepository());
                                                   }).singleInstance();
                builder->registerType<InteriorsEntitiesPinsController>().as<IInteriorsEntitiesPinsController>().singleInstance();
            }
        }
    }
}