// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "AboutPage.h"
#include "IAboutPageViewModule.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        class AboutPageViewModule: public IAboutPageViewModule, private Eegeo::NonCopyable
        {
        private:
            AboutPageViewController* m_pAboutPageViewController;
            
        public:
            AboutPageViewModule(IAboutPageModel& aboutPageModel,
                                IAboutPageViewModel& aboutPageViewModel);
            
            ~AboutPageViewModule();
            
            AboutPageViewController& GetAboutPageViewController() const;
            
            AboutPageView& GetAboutPageView() const;
        };
    }
}
