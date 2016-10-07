// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <InteriorsExplorer/View/InteriorsExplorerViewJni.h>
#include "InteriorsExplorerViewModule.h"
#include "ScreenProperties.h"
#include "InteriorsExplorerView.h"
#include "InteriorsExplorerController.h"
#include "AndroidAppThreadAssertionMacros.h"

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
				ASSERT_UI_THREAD
				RegisterLeaf<IInteriorsExplorerView>();
			}
        }
    }
}
