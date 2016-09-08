// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroViewModule.h"
#include "InitialExperienceIntroView.h"
#include "InitialExperienceIntroBackgroundView.h"
#include "InitialExperienceIntroController.h"
#include "InitialExperienceIntroViewInterop.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            void InitialExperienceIntroViewModule::Register(const TContainerBuilder &builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = [[InitialExperienceIntroBackgroundView alloc] initView];
                                                     return std::make_shared<InitialExperienceIntroBackgroundViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto backgroundView = context.resolve<InitialExperienceIntroBackgroundViewWrapper>();
                                                     auto view = [[InitialExperienceIntroView alloc] initView: backgroundView->Get()];
                                                     return std::make_shared<InitialExperienceIntroViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<InitialExperienceIntroViewWrapper>();
                                                     return Hypodermic::makeExternallyOwned(*[view->Get() getInterop]);
                                                 }).as<IInitialExperienceIntroView>().singleInstance();
                builder->registerType<InitialExperienceIntroController>().singleInstance();
            }
            
            void InitialExperienceIntroViewModule::RegisterLeaves()
            {
                RegisterLeaf<InitialExperienceIntroController>();
            }
        }
    }
}