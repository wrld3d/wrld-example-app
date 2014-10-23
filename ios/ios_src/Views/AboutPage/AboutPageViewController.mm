// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AboutPageViewController.h"
#include "Types.h"
#include "AboutPageView.h"
#include "IAboutPageViewModel.h"
#include "ICallback.h"
#include "AboutPageViewControllerInterop.h"

@interface AboutPageViewController()<UIGestureRecognizerDelegate>
{
    UITapGestureRecognizer* _tapGestureRecogniser;
}
@end

@implementation AboutPageViewController

- (id)initWithParams:(ExampleApp::AboutPage::IAboutPageModel*)pAboutPageModel
                    :(ExampleApp::AboutPage::IAboutPageViewModel*)pAboutPageViewModel;
{
    if(self = [super init])
    {
        m_pAboutPageModel = pAboutPageModel;
        m_pAboutPageViewModel = pAboutPageViewModel;
        m_pInterop = Eegeo_NEW(ExampleApp::AboutPage::AboutPageViewControllerInterop)(self, *m_pAboutPageViewModel);
        
        self.pAboutPageView = [[[AboutPageView alloc] initWithController:self] autorelease];
        [self.pAboutPageView setFrame:[self view].bounds];
        self.view = self.pAboutPageView;
        
        if(m_pAboutPageViewModel->IsOpen())
        {
            [self open];
        }
        
        _tapGestureRecogniser = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_tapTabGesture:)];
        [_tapGestureRecogniser setDelegate:self];
        [[self.pAboutPageView pCloseButton] addGestureRecognizer: _tapGestureRecogniser];
    }
    
    return self;
}

- (void)dealloc
{
    [_pAboutPageView release];
    
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (void) open
{
    if(m_pAboutPageViewModel->TryAcquireReactorControl())
    {
        [self.pAboutPageView setFullyActive];
        [self.pAboutPageView setContent:m_pAboutPageModel];
    }
}

- (void) close
{
    [self.pAboutPageView setFullyInactive];
}

- (void)_tapTabGesture:(UITapGestureRecognizer *)recognizer
{
    m_pAboutPageViewModel->Close();
}

@end


