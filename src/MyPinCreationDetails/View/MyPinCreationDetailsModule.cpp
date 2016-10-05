// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsModule.h"
#include "MyPinCreationDetailsViewModel.h"
#include "IReactionControllerModel.h"
#include "MyPinCreationDetailsController.h"
#include "IMyPinCreationDetailsView.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            void MyPinCreationDetailsModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<MyPinCreationDetailsViewModel>().as<IMyPinCreationDetailsViewModel>().singleInstance();
                builder->registerType<View::MyPinCreationDetailsController>().singleInstance();
            }
            
            void MyPinCreationDetailsModule::RegisterUiLeaves()
            {
                RegisterLeaf<View::MyPinCreationDetailsController>();
            }
            
            void MyPinCreationDetailsModule::RegisterOpenablesAndReactors()
            {
                RegisterOpenable(&Resolve<IMyPinCreationDetailsViewModel>()->GetOpenableControl());
            }
        }
    }
}
