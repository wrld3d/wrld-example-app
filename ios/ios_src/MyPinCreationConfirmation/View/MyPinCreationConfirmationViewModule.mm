// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "MyPinCreationConfirmationViewModule.h"
#include "RenderContext.h"
#include "MyPinCreationConfirmationView.h"
#include "MyPinCreationConfirmationController.h"
#include "MyPinCreationConfirmationViewInterop.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            void MyPinCreationConfirmationViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                                     auto view = [[MyPinCreationConfirmationView alloc] initWithParams
                                                                  :screenProperties->GetScreenWidth()
                                                                  :screenProperties->GetScreenHeight()
                                                                  :screenProperties->GetPixelScale()
                                                                  ];
                                                     return std::make_shared<MyPinCreationConfirmationViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<MyPinCreationConfirmationViewWrapper>();
                                                     return Hypodermic::makeExternallyOwned(*[view->Get() getInterop]);
                                                 }).as<IMyPinCreationConfirmationView>().singleInstance();
            }
        }
    }
}
