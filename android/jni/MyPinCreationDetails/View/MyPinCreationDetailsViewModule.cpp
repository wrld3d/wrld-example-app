// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsViewModule.h"
#include "MyPinCreationDetailsView.h"
#include "MyPinCreationDetailsController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
			void MyPinCreationDetailsViewModule::Register(const TContainerBuilder& builder)
			{
				builder->registerType<MyPinCreationDetailsView>().as<IMyPinCreationDetailsView>().singleInstance();
			}

			void MyPinCreationDetailsViewModule::RegisterUiLeaves()
			{
				ASSERT_UI_THREAD
				RegisterLeaf<IMyPinCreationDetailsView>();
			}
        }
    }
}
