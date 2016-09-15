// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonModule.h"
#include "FlattenButtonViewModel.h"
#include "FlattenButtonModel.h"
#include "FlattenButtonController.h"
#include "FlattenButtonViewStateChangedObserver.h"
#include "FlattenButtonModelStateChangedObserver.h"
#include "IMapModeModel.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace SdkModel
        {
            void FlattenButtonModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<FlattenButtonModel>().as<IFlattenButtonModel>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<View::FlattenButtonViewModel>(context.resolve<Eegeo::Helpers::IIdentityProvider>(), false);
                                                   }).as<View::IFlattenButtonViewModel>().singleInstance();
                builder->registerType<FlattenButtonViewStateChangedObserver>().singleInstance();
                builder->registerType<FlattenButtonModelStateChangedObserver>().singleInstance();
                builder->registerType<View::FlattenButtonController>().singleInstance();
            }
            
            void FlattenButtonModule::RegisterLeaves()
            {
                RegisterLeaf<View::FlattenButtonController>();
                RegisterLeaf<FlattenButtonModelStateChangedObserver>();
                RegisterLeaf<FlattenButtonViewStateChangedObserver>();
            }
            
            void FlattenButtonModule::RegisterOpenablesAndReactors()
            {
                RegisterReactor(&Resolve<View::IFlattenButtonViewModel>()->GetScreenControlViewModel());
            }
        }
    }
}
