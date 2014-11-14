// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "FlattenButtonViewController.h"
#include "FlattenButtonView.h"
#include "FlattenButtonViewModel.h"
#include "FlattenButtonViewControllerInterop.h"
#include "IFlattenButtonModel.h"
#include "FlattenButtonViewStateChangedMessage.h"

@implementation FlattenButtonViewController

- (id)initWithParams:(ExampleApp::FlattenButton::IFlattenButtonViewModel*)pViewModel
    :(ExampleApp::FlattenButton::IFlattenButtonModel*)pModel
    :(FlattenButtonView*)pButtonView
    :(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus*)pUiToNativeMessageBus
    :(ExampleApp::ExampleAppMessaging::NativeToUiMessageBus*)pNativeToUiMessageBus
{
	if(self = [super init])
	{
		self.pButtonView = pButtonView;
		[pButtonView setController:self];
		self.view = pButtonView;

		m_pViewModel = pViewModel;
		m_pModel = pModel;
		m_pInterop = Eegeo_NEW(ExampleApp::FlattenButton::FlattenButtonViewControllerInterop)(self, *pNativeToUiMessageBus, *m_pViewModel);
		m_pUiToNativeMessageBus = pUiToNativeMessageBus;

		[self.pButtonView setOnScreenStateToIntermediateValue:m_pViewModel->OnScreenState()];
	}

	return self;
}

- (void)dealloc
{
	Eegeo_DELETE m_pInterop;
	[super dealloc];
}

- (void) setSelected:(BOOL)selected
{
	m_pUiToNativeMessageBus->Publish(ExampleApp::FlattenButton::FlattenButtonViewStateChangedMessage(selected));
}

- (void) handleModelStateChanged:(BOOL)flattened
{
	[self.pButtonView setSelected:flattened];
}

- (void) handleScreenStateChanged:(float)onScreenState
{
	if(m_pViewModel->IsFullyOffScreen())
	{
		[self.pButtonView setFullyOffScreen];
	}
	else if(m_pViewModel->IsFullyOnScreen())
	{
		[self.pButtonView setFullyOnScreen];
	}
	else
	{
		[self.pButtonView setOnScreenStateToIntermediateValue:m_pViewModel->OnScreenState()];
	}
}

@end
