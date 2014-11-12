// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "AboutPage.h"
#include "AboutPageViewModule.h"
#include "IAboutPageViewController.h"
#include "ICallback.h"

namespace ExampleApp
{
namespace AboutPage
{
class AboutPageViewController : public IAboutPageViewController, private Eegeo::NonCopyable
{
	AndroidNativeState& m_nativeState;
	AboutPage::IAboutPageModel& m_aboutPageModel;
	AboutPage::IAboutPageViewModel& m_aboutPageViewModel;
	Eegeo::Helpers::ICallback0* m_pAboutPageOpenedCallback;
	Eegeo::Helpers::ICallback0* m_pAboutPageClosedCallback;

	jclass m_uiViewClass;
	jobject m_uiView;

public:
	AboutPageViewController(
	    AndroidNativeState& nativeState,
	    AboutPage::IAboutPageModel& aboutPageModel,
	    AboutPage::IAboutPageViewModel& viewModel
	);

	~AboutPageViewController();

	void HandleCloseButtonPressed();

private:

	void AboutPageOpenedCallback();

	void AboutPageClosedCallback();
};
}
}
