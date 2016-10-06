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
				builder->registerType<MyPinCreationInitiationView>().as<IMyPinCreationInitiationView>().singleInstance();
				builder->registerType<MyPinCreationConfirmationView>().as<IMyPinCreationConfirmationView>().singleInstance();
			}

			void MyPinCreationViewModule::RegisterUiLeaves()
			{
				Eegeo_TTY("MyPinCreationViewModule::RegisterUiLeaves begin");
				ASSERT_UI_THREAD
				RegisterLeaf<IMyPinCreationInitiationView>();
				RegisterLeaf<IMyPinCreationConfirmationView>();
				Eegeo_TTY("MyPinCreationViewModule::RegisterUiLeaves end");
			}
        }
    }
}
