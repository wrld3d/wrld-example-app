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
				builder->registerType<MyPinDetailsView>().as<IMyPinDetailsView>().singleInstance();
			}

        	void MyPinDetailsViewModule::RegisterUiLeaves()
        	{
				ASSERT_UI_THREAD
        		RegisterLeaf<IMyPinDetailsView>();
        	}
        }
    }
}
