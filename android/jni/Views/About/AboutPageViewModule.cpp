// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AboutPageViewModule.h"
#include "AboutPage.h"
#include "AboutPageViewController.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        AboutPageViewModule::AboutPageViewModule(
			AndroidNativeState& nativeState,
			AboutPage::IAboutPageModel& aboutPageModel,
			AboutPage::IAboutPageViewModel& aboutPageViewModel
		)
        {
            m_pAboutPageViewController = Eegeo_NEW(AboutPageViewController)(
				nativeState,
				aboutPageModel,
				aboutPageViewModel
            );
        }
        
        AboutPageViewModule::~AboutPageViewModule()
        {
            Eegeo_DELETE(m_pAboutPageViewController);
        }
        
        IAboutPageViewController& AboutPageViewModule::GetAboutPageViewController() const
        {
            return *m_pAboutPageViewController;
        }
    }
}
