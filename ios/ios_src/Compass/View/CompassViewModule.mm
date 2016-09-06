// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "CompassViewModule.h"
#include "RenderContext.h"
#include "CompassView.h"
#include "ScreenProperties.h"
#include "CompassViewInterop.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            void CompassViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                                     auto view = [[CompassView alloc] initWithParams
                                                                  :screenProperties->GetScreenWidth()
                                                                  :screenProperties->GetScreenHeight()
                                                                  :screenProperties->GetPixelScale()
                                                                  ];
                                                     return std::make_shared<CompassViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<CompassViewWrapper>();
                                                     return Hypodermic::makeExternallyOwned(*[view->Get() getInterop]);
                                                 }).as<ICompassView>().singleInstance();
              }
        }
    }
}
