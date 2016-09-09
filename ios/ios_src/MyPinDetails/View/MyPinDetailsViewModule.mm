// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsViewModule.h"
#include "IMyPinDetailsViewModel.h"
#include "MyPinDetailsController.h"
#include "MyPinDetailsVIew.h"
#include "ScreenProperties.h"
#include "MyPinDetailsViewInterop.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            void MyPinDetailsViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                                     auto view = [[MyPinDetailsView alloc] initWithParams:screenProperties->GetScreenWidth() :screenProperties->GetScreenHeight()];
                                                     return std::make_shared<MyPinDetailsViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<MyPinDetailsViewWrapper>();
                                                     return Hypodermic::makeExternallyOwned(*[view->Get() getInterop]);
                                                 }).as<IMyPinDetailsView>().singleInstance();
            }
        }
    }
}
