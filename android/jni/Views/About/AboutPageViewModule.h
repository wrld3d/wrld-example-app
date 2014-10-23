// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "AboutPage.h"
#include "AboutPageViewIncludes.h"
#include "IAboutPageViewModule.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        class AboutPageViewModule: public IAboutPageViewModule, private Eegeo::NonCopyable
        {
        private:
        	AboutPage::IAboutPageViewController* m_pAboutPageViewController;

        public:
            AboutPageViewModule(
				AndroidNativeState& nativeState,
				AboutPage::IAboutPageModel& aboutPageModel,
				AboutPage::IAboutPageViewModel& aboutPageViewModel
        	);
            
            ~AboutPageViewModule();
            
            IAboutPageViewController& GetAboutPageViewController() const;
        };
    }
}
