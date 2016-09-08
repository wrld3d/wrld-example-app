// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsViewModule.h"
#include "IOptionsViewModel.h"
#include "OptionsView.h"
#include "OptionsController.h"
#include "OptionsViewInterop.h"
#include "IHttpCache.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            void OptionsViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = [[OptionsView alloc] initView];
                                                     return std::make_shared<OptionsViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<OptionsViewWrapper>();
                                                     return Hypodermic::makeExternallyOwned(*[view->Get() getInterop]);
                                                 }).as<IOptionsView>().singleInstance();
            }
        }
    }
}
