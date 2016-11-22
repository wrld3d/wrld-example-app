// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonViewModule.h"
#include "FlattenButtonView.h"
#include "WindowsAppThreadAssertionMacros.h"

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
                RegisterLeaf<IFlattenButtonView>();
            }
        }
    }
}
