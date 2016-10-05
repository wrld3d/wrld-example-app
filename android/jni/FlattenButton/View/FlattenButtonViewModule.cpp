// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonViewModule.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "FlattenButtonView.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {

			void FlattenButtonViewModule::Register(const TContainerBuilder& builder)
			{
				ASSERT_UI_THREAD
				builder->registerType<FlattenButtonView>().as<IFlattenButtonView>().singleInstance();
			}

			void FlattenButtonViewModule::RegisterLeaves()
			{
				ASSERT_UI_THREAD
				RegisterLeaf<IFlattenButtonView>();
			}
        }
    }
}
