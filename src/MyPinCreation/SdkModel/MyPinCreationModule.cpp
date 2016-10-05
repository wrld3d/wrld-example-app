// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationModule.h"
#include "MyPinCreationModel.h"
#include "MyPinCreationModelObserver.h"
#include "MyPinCreationViewStateChangedHandler.h"
#include "MyPinCreationViewSavePinHandler.h"
#include "MyPinCreationInitiationViewModel.h"
#include "MyPinCreationConfirmationViewModel.h"
#include "MyPinCreationCompositeViewModel.h"
#include "IMyPinsService.h"
#include "ISearchRefreshService.h"
#include "IReactionControllerModel.h"
#include "IMenuViewModel.h"
#include "MyPinCreationInitiationController.h"
#include "MyPinCreationConfirmationController.h"
#include "IMyPinCreationInitiationView.h"
#include "IMyPinCreationConfirmationView.h"
#include "IMyPinCreationDetailsViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            void MyPinCreationModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<MyPinCreationModel>().as<IMyPinCreationModel>().singleInstance();
                builder->registerType<MyPinCreationModelObserver>().singleInstance();
                builder->registerType<MyPinCreationViewStateChangedHandler>().singleInstance();
                builder->registerType<MyPinCreationViewSavePinHandler>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<View::MyPinCreationInitiationViewModel>(context.resolve<Eegeo::Helpers::IIdentityProvider>(), false);
                                                   }).as<View::IMyPinCreationInitiationViewModel>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<View::MyPinCreationConfirmationViewModel>(context.resolve<Eegeo::Helpers::IIdentityProvider>()->GetNextIdentity(), false, context.resolve<Reaction::View::IReactionControllerModel>());
                                                   }).as<View::IMyPinCreationConfirmationViewModel>().singleInstance();
                builder->registerType<View::MyPinCreationCompositeViewModel>().as<View::IMyPinCreationCompositeViewModel>().singleInstance();
                builder->registerType<View::MyPinCreationInitiationController>().singleInstance();
            }
            
            void MyPinCreationModule::RegisterNativeLeaves()
            {
                RegisterLeaf<MyPinCreationViewSavePinHandler>();
                RegisterLeaf<MyPinCreationViewStateChangedHandler>();
                RegisterLeaf<MyPinCreationModelObserver>();
            }
            
            void MyPinCreationModule::RegisterUiLeaves()
            {
                RegisterLeaf<View::MyPinCreationInitiationController>();
                RegisterLeaf<View::MyPinCreationConfirmationController>();
                RegisterLeaf<View::IMyPinCreationCompositeViewModel>();
            }
            
            void MyPinCreationModule::RegisterOpenablesAndReactors()
            {
                RegisterOpenable(&Resolve<View::IMyPinCreationConfirmationViewModel>()->GetOpenableControlViewModel());
                RegisterReactor(&Resolve<View::IMyPinCreationInitiationViewModel>()->GetScreenControlViewModel());
            }
        }
    }
}
