// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldAreaLoaderModule.h"
#include "WorldAreaLoader.h"
#include "WorldAreaLoaderModel.h"
#include "PrecacheService.h"

namespace ExampleApp
{
    namespace WorldAreaLoader
    {
        namespace SdkModel
        {
            void WorldAreaLoaderModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            {
                builder->registerType<WorldAreaLoaderModel>().as<IWorldAreaLoaderModel>().singleInstance();
            }
        }
    }
}
