// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ViewController.h"
#include "AppLocationDelegate.h"

const std::string ApiKey = "OBTAIN API_KEY FROM https://appstore.eegeo.com AND INSERT IT HERE";

using namespace Eegeo::iOS;

@implementation ViewController

- (void)viewDidLoad
{
	[super viewDidLoad];
    
	m_previousTimestamp = CFAbsoluteTimeGetCurrent();
	self.preferredFramesPerSecond = 60.0f;
    
    m_pAppRunner = new AppRunner(ApiKey, *self);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
	CFTimeInterval timeNow = CFAbsoluteTimeGetCurrent();
	CFTimeInterval frameDuration = timeNow - m_previousTimestamp;
    m_pAppRunner->Update(frameDuration);
    
	const GLenum discards[]  = {GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT};
	Eegeo_GL(glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 2, discards));
    
    m_previousTimestamp = timeNow;
}

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
	return YES;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
	return YES;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return m_pAppRunner->ShouldAutoRotateToInterfaceOrientation(interfaceOrientation);
}

@end