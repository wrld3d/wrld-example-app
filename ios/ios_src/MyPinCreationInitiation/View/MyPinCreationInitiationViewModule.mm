// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "MyPinCreationInitiationViewModule.h"
#include "RenderContext.h"
#include "MyPinCreationInitiationView.h"
#include "MyPinCreationInitiationController.h"
#include "MyPinCreationInitiationViewInterop.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            void MyPinCreationInitiationViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                                     auto view = [[MyPinCreationInitiationView alloc] initWithParams
                                                                  :screenProperties->GetScreenWidth()
                                                                  :screenProperties->GetScreenHeight()
                                                                  :screenProperties->GetPixelScale()
                                                                  ];
                                                     return std::make_shared<MyPinCreationInitiationViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<MyPinCreationInitiationViewWrapper>();
                                                     return Hypodermic::makeExternallyOwned(*[view->Get() getInterop]);
                                                 }).as<IMyPinCreationInitiationView>().singleInstance();
            }
        }
    }
}
