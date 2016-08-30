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
            MapModeModule::MapModeModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            : m_builder(builder)
            {
            }
            
            void MapModeModule::Register()
            {
                m_builder->registerType<MapModeModel>().as<IMapModeModel>().singleInstance();
                m_builder->registerType<MapModeController>().singleInstance();
            }
        }
    }
}