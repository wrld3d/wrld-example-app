// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AboutPageView.h"
#include "AboutPage.h"

namespace ExampleApp
{
namespace AboutPage
{
class AboutPageViewControllerInterop;
}
}

@interface AboutPageViewController : UIViewController
{
	ExampleApp::AboutPage::IAboutPageModel* m_pAboutPageModel;
	ExampleApp::AboutPage::IAboutPageViewModel* m_pAboutPageViewModel;
	ExampleApp::AboutPage::AboutPageViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(ExampleApp::AboutPage::IAboutPageModel*)pAboutPageModel
    :(ExampleApp::AboutPage::IAboutPageViewModel*)pAboutPageViewModel;

- (void) open;

- (void) close;

@property (nonatomic, retain) AboutPageView* pAboutPageView;

@end
