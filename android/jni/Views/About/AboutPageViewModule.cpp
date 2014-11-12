// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AboutPageViewModule.h"
#include "AboutPage.h"
#include "AboutPageViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

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
	ASSERT_UI_THREAD

	m_pAboutPageViewController = Eegeo_NEW(AboutPageViewController)(
	                                 nativeState,
	                                 aboutPageModel,
	                                 aboutPageViewModel
	                             );
}

AboutPageViewModule::~AboutPageViewModule()
{
	ASSERT_UI_THREAD

	Eegeo_DELETE(m_pAboutPageViewController);
}

IAboutPageViewController& AboutPageViewModule::GetAboutPageViewController() const
{
	ASSERT_UI_THREAD

	return *m_pAboutPageViewController;
}
}
}
