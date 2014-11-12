// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AboutPageViewModule.h"
#include "IAboutPageViewModel.h"
#include "AboutPageViewController.h"

namespace ExampleApp
{
namespace AboutPage
{
AboutPageViewModule::AboutPageViewModule(IAboutPageModel& aboutPageModel,
        IAboutPageViewModel& aboutPageViewModel)
{
	m_pAboutPageViewController = [[AboutPageViewController alloc] initWithParams :&aboutPageModel
	                              :&aboutPageViewModel];
}

AboutPageViewModule::~AboutPageViewModule()
{
	[m_pAboutPageViewController release];
}

AboutPageViewController& AboutPageViewModule::GetAboutPageViewController() const
{
	return *m_pAboutPageViewController;
}

AboutPageView& AboutPageViewModule::GetAboutPageView() const
{
	return *[m_pAboutPageViewController pAboutPageView];
}
}
}
