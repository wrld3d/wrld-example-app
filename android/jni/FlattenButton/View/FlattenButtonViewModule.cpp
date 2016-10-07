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
				builder->registerType<FlattenButtonView>().as<IFlattenButtonView>().singleInstance();
			}

			void FlattenButtonViewModule::RegisterUiLeaves()
			{
				ASSERT_UI_THREAD
				RegisterLeaf<IFlattenButtonView>();
			}
        }
    }
}
