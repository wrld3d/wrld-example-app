// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinDetailsViewController.h"
#include "Types.h"
#include "MyPinDetailsView.h"
#include "IMyPinDetailsViewModel.h"
#include "ICallback.h"
#include "MyPinDetailsViewControllerInterop.h"
#include "MyPinDetailsViewRemovePinMessage.h"


@implementation MyPinDetailsViewController

- (id)initWithParams:(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus*) pUiToNativeMessageBus
                    :(ExampleApp::MyPinDetails::IMyPinDetailsViewModel*)pMyPinDetailsViewModel;
{
	if(self = [super init])
	{
        m_pUiToNativeMessageBus = pUiToNativeMessageBus;
		m_pMyPinDetailsViewModel = pMyPinDetailsViewModel;
		m_pInterop = Eegeo_NEW(ExampleApp::MyPinDetails::MyPinDetailsViewControllerInterop)(self, *m_pMyPinDetailsViewModel);

		self.pMyPinDetailsView = [[[MyPinDetailsView alloc] initWithController:self] autorelease];
		[self.pMyPinDetailsView setFrame:[self view].bounds];
		self.view = self.pMyPinDetailsView;

		if(m_pMyPinDetailsViewModel->IsOpen())
		{
			[self openWithModel:m_pMyPinDetailsViewModel->GetMyPinModel()];
		}

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

    [self.pMyPinDetailsView setContent:&myPinModel];
	[self.pMyPinDetailsView setFullyActive];
}

- (void) close
{
	[self.pMyPinDetailsView setFullyInactive];
}

- (void) handleCloseButtonPressed
{
    m_pMyPinDetailsViewModel->Close();
}

- (void) handleRemovePinButtonPressed
{
    if (m_pMyPinDetailsViewModel->IsOpen())
    {
        const ExampleApp::MyPins::MyPinModel& myPinModel = m_pMyPinDetailsViewModel->GetMyPinModel();
        ExampleApp::MyPinDetails::MyPinDetailsViewRemovePinMessage message(myPinModel.Identifier());
        m_pUiToNativeMessageBus->Publish(message);

        m_pMyPinDetailsViewModel->Close();
    }
}

@end


