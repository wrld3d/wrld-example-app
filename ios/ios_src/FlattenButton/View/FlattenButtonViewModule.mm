// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "FlattenButtonViewModule.h"
#include "RenderContext.h"
#include "FlattenButtonView.h"
#include "ScreenProperties.h"
#include "FlattenButtonController.h"
#include "FlattenButtonViewInterop.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            void FlattenButtonViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                                     auto view = [[FlattenButtonView alloc] initWithDimensions
                                                                  :screenProperties->GetScreenWidth()
                                                                  :screenProperties->GetScreenHeight()
                                                                  :screenProperties->GetPixelScale()
                                                                  ];
                                                     return std::make_shared<FlattenButtonViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<FlattenButtonViewWrapper>();
                                                     return Hypodermic::makeExternallyOwned(*[view->Get() getInterop]);
                                                 }).as<IFlattenButtonView>().singleInstance();
            }
        }
    }
}
