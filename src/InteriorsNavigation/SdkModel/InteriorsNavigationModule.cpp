// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsNavigationModule.h"
#include "InteriorsNavigationService.h"
#include "ILocationService.h"
#include "InteriorsCameraController.h"
#include "GlobeCameraTouchController.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace InteriorsNavigation
    {
        namespace SdkModel
        {
            InteriorsNavigationModule::InteriorsNavigationModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            : m_builder(builder)
            {
            }
            
            void InteriorsNavigationModule::Register()
            {
                m_builder->registerType<InteriorsNavigationService>().as<IInteriorsNavigationService>().singleInstance();
            }
        }
    }
}
