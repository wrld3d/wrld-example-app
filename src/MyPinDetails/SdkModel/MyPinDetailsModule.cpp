// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsModule.h"
#include "MyPinDetailsViewModel.h"
#include "MyPinDetailsDisplayService.h"
#include "MyPinDetailsViewRemovePinHandler.h"
#include "MyPinDetailsModelSelectedObserver.h"
#include "IReactionControllerModel.h"
#include "ISearchResultPoiViewModel.h"
#include "IMyPinsService.h"
#include "MyPinDetailsController.h"
#include "IMyPinDetailsView.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace SdkModel
        {
            void MyPinDetailsModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<View::MyPinDetailsViewModel>().as<View::IMyPinDetailsViewModel>().singleInstance();
                builder->registerType<View::MyPinDetailsDisplayService>().as<View::IMyPinDetailsDisplayService>().singleInstance();
                builder->registerType<View::MyPinDetailsModelSelectedObserver>().singleInstance();
                builder->registerType<MyPinDetailsViewRemovePinHandler>().singleInstance();
                builder->registerType<View::MyPinDetailsController>().singleInstance();
            }
            
            void MyPinDetailsModule::RegisterNativeLeaves()
            {
                RegisterLeaf<MyPinDetailsViewRemovePinHandler>();
            }
            
            void MyPinDetailsModule::RegisterUiLeaves()
            {
                RegisterLeaf<View::MyPinDetailsController>();
                RegisterLeaf<View::MyPinDetailsModelSelectedObserver>();
            }
            
            void MyPinDetailsModule::RegisterOpenablesAndReactors()
            {
                RegisterOpenable(&Resolve<View::IMyPinDetailsViewModel>()->GetOpenableControl());
            }
        }
    }
}
