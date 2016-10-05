// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VisualMapModule.h"
#include "VisualMapModel.h"
#include "VisualMapStateHistory.h"
#include "VisualMapController.h"
#include "VisualMapService.h"
#include "VisualMapState.h"

#include "EnvironmentFlatteningService.h"
#include "ICityThemesService.h"
#include "CityThemeData.h"
#include "ICityThemesUpdater.h"

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            void VisualMapModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       VisualMapState initalState("Summer", "DayDefault", false);
                                                       return std::make_shared<VisualMapModel>(initalState);
                                                   }).as<IVisualMapModel>().singleInstance();
                builder->registerType<VisualMapStateHistory>().as<IVisualMapStateHistory>().singleInstance();
                builder->registerType<VisualMapController>().as<IVisualMapController>().singleInstance();
                builder->registerType<VisualMapService>().as<IVisualMapService>().singleInstance();
            }
            
            void VisualMapModule::RegisterNativeLeaves()
            {
                RegisterLeaf<IVisualMapController>();
            }
        }
    }
}