// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MapModeModule.h"
#include "MapModeModel.h"
#include "MapModeController.h"
#include "IVisualMapService.h"

namespace ExampleApp
{
    namespace MapMode
    {
        namespace SdkModel
        {
            void MapModeModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<MapModeModel>().as<IMapModeModel>().singleInstance();
                builder->registerType<MapModeController>().singleInstance();
            }
            
            void MapModeModule::RegisterNativeLeaves()
            {
                RegisterLeaf<MapModeController>();
            }
        }
    }
}