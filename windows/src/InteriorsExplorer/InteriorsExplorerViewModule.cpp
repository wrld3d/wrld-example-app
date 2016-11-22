// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerViewModule.h"
#include "ScreenProperties.h"
#include "InteriorsExplorerView.h"
#include "InteriorsExplorerController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            void InteriorsExplorerViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<InteriorsExplorerView>().as<IInteriorsExplorerView>().singleInstance();
            }

            void InteriorsExplorerViewModule::RegisterUiLeaves()
            {
                RegisterLeaf<IInteriorsExplorerView>();
            }
        }
    }
}