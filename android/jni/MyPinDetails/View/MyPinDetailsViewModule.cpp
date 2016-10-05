// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsViewModule.h"
#include "MyPinDetailsView.h"
#include "MyPinDetailsController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
			void MyPinDetailsViewModule::Register(const TContainerBuilder& builder)
			{
				ASSERT_UI_THREAD
				builder->registerType<MyPinDetailsView>().as<IMyPinDetailsView>().singleInstance();
			}

        	void MyPinDetailsViewModule::RegisterLeaves()
        	{
				ASSERT_UI_THREAD
        		RegisterLeaf<IMyPinDetailsView>();
        	}
        }
    }
}
