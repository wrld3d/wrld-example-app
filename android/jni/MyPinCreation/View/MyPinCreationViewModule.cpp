// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationViewModule.h"
#include "MyPinCreationInitiationView.h"
#include "MyPinCreationInitiationController.h"
#include "MyPinCreationConfirmationView.h"
#include "MyPinCreationConfirmationController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
			void MyPinCreationViewModule::Register(const TContainerBuilder& builder)
			{
				ASSERT_UI_THREAD
				builder->registerType<MyPinCreationInitiationView>().as<IMyPinCreationInitiationView>().singleInstance();
				builder->registerType<MyPinCreationConfirmationView>().as<IMyPinCreationConfirmationView>().singleInstance();
			}

			void MyPinCreationViewModule::RegisterLeaves()
			{
				ASSERT_UI_THREAD
				RegisterLeaf<IMyPinCreationInitiationView>();
				RegisterLeaf<IMyPinCreationConfirmationView>();
			}
        }
    }
}
