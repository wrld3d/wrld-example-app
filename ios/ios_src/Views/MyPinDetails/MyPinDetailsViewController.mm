// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinDetailsViewController.h"
#include "Types.h"
#include "MyPinDetailsView.h"
#include "IMyPinDetailsViewModel.h"
#include "ICallback.h"
#include "MyPinDetailsViewControllerInterop.h"

@interface MyPinDetailsViewController()<UIGestureRecognizerDelegate>
{
	UITapGestureRecognizer* _tapGestureRecogniser;
}
@end

@implementation MyPinDetailsViewController

- (id)initWithParams:(ExampleApp::MyPinDetails::IMyPinDetailsViewModel*)pMyPinDetailsViewModel;
{
	if(self = [super init])
	{
		m_pMyPinDetailsViewModel = pMyPinDetailsViewModel;
		m_pInterop = Eegeo_NEW(ExampleApp::MyPinDetails::MyPinDetailsViewControllerInterop)(self, *m_pMyPinDetailsViewModel);

		self.pMyPinDetailsView = [[[MyPinDetailsView alloc] initWithController:self] autorelease];
		[self.pMyPinDetailsView setFrame:[self view].bounds];
		self.view = self.pMyPinDetailsView;

		if(m_pMyPinDetailsViewModel->IsOpen())
		{
			[self openWithModel:m_pMyPinDetailsViewModel->GetMyPinModel()];
		}

		_tapGestureRecogniser = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_tapTabGesture:)] autorelease];
		[_tapGestureRecogniser setDelegate:self];
		[[self.pMyPinDetailsView pCloseButton] addGestureRecognizer: _tapGestureRecogniser];
	}

	return self;
}

- (void)dealloc
{
	[_pMyPinDetailsView release];

	Eegeo_DELETE m_pInterop;
	[super dealloc];
}

- (void) openWithModel:(const ExampleApp::MyPins::MyPinModel&)myPinModel
{
	if(!m_pMyPinDetailsViewModel->TryAcquireReactorControl())
	{
		m_pMyPinDetailsViewModel->Close();
		return;
	}

	[self.pMyPinDetailsView setFullyActive];
	[self.pMyPinDetailsView setContent:&myPinModel];
}

- (void) close
{
	[self.pMyPinDetailsView setFullyInactive];
}

- (void)_tapTabGesture:(UITapGestureRecognizer *)recognizer
{
	m_pMyPinDetailsViewModel->Close();
}

@end


