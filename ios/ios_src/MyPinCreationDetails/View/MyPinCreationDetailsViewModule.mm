// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsViewModule.h"
#include "MyPinCreationDetailsView.h"
#include "MyPinCreationDetailsController.h"
#include "ScreenProperties.h"
#include "ViewController.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            void MyPinCreationDetailsViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                                     auto viewController = context.resolve<ViewControllerWrapper>();
                                                     auto view = [[MyPinCreationDetailsView alloc] initWithParams: screenProperties->GetScreenWidth()
                                                                                                               : screenProperties->GetScreenHeight()
                                                                                                               : viewController->Get()];
                                                     return std::make_shared<MyPinCreationDetailsViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<MyPinCreationDetailsViewWrapper>();
                                                     return Hypodermic::makeExternallyOwned(*[view->Get() getInterop]);
                                                 }).as<IMyPinCreationDetailsView>().singleInstance();
            }
        }
    }
}
