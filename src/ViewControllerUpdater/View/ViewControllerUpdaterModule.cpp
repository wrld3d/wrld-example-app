// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ViewControllerUpdaterModule.h"
#include "ViewControllerUpdaterModel.h"

namespace ExampleApp
{
    namespace ViewControllerUpdater
    {
        namespace View
        {
            void ViewControllerUpdaterModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            {
                builder->registerType<ViewControllerUpdaterModel>().as<IViewControllerUpdaterModel>().singleInstance();
            }
        }
    }
}
