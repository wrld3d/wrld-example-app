// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageViewModule.h"
#include "IAboutPageViewModel.h"
#include "AboutPageView.h"
#include "AboutPageController.h"
#include "AboutPageViewInterop.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            void AboutPageViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = [[AboutPageView alloc] initView];
                                                     return std::make_shared<AboutPageViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<AboutPageViewWrapper>();
                                                     return Hypodermic::makeExternallyOwned(*[view->Get() getInterop]);
                                                 }).as<IAboutPageView>().singleInstance();
            }
        }
    }
}
