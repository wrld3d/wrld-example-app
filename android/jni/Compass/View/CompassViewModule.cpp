// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassViewModule.h"
#include "CompassView.h"
#include "CompassController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
        	void CompassViewModule::Register(const TContainerBuilder& builder)
        	{
        		builder->registerType<CompassView>().as<ICompassView>().singleInstance();
        	}

			void CompassViewModule::RegisterUiLeaves()
			{
        		ASSERT_UI_THREAD
				RegisterLeaf<ICompassView>();
			}
        }
    }
}
