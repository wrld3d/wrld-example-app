// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerViewModule.h"
#include "ScreenProperties.h"
#include "InteriorsExplorerView.h"
#include "InteriorsExplorerViewInterop.h"
#include "InteriorsExplorerController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            void InteriorsExplorerViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                                     auto view = [[InteriorsExplorerTutorialView alloc] initWithParams
                                                                  :screenProperties->GetScreenWidth()
                                                                  :screenProperties->GetScreenHeight()
                                                                  :screenProperties->GetPixelScale()
                                                                  ];
                                                     return std::make_shared<InteriorsExplorerTutorialViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                                     auto tutorialView = context.resolve<InteriorsExplorerTutorialViewWrapper>();
                                                     auto view = [[InteriorsExplorerView alloc] initWithParams
                                                                  :screenProperties->GetScreenWidth()
                                                                  :screenProperties->GetScreenHeight()
                                                                  :screenProperties->GetPixelScale()
                                                                  :*tutorialView->Get()
                                                                  ];
                                                     return std::make_shared<InteriorsExplorerViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<InteriorsExplorerViewWrapper>();
                                                     return Hypodermic::makeExternallyOwned(*[view->Get() getInterop]);
                                                 }).as<IInteriorsExplorerView>().singleInstance();
            }
        }
    }
}
