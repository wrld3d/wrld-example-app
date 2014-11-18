// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationDetailsViewController.h"
#include "MyPinCreationDetailsViewControllerInterop.h"
#include "MyPinCreationDetailsView.h"
#include "MyPinCreationDetailsViewModel.h"
#include "MyPinCreationViewStateChangedMessage.h"
#include "MyPinCreationViewSavePinMessage.h"

#include <string>

@implementation MyPinCreationDetailsViewController

- (id)initWithParams:(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus*) pUiToNativeMessageBus
                    :(ExampleApp::MyPinCreationDetails::IMyPinCreationDetailsViewModel*)pViewModel
{
    if(self = [super init])
    {
        m_pUiToNativeMessageBus = pUiToNativeMessageBus;
        m_pViewModel = pViewModel;
        m_pInterop = Eegeo_NEW(ExampleApp::MyPinCreationDetails::MyPinCreationDetailsViewControllerInterop)(self, *m_pViewModel);
        
        self.pMyPinCreationDetailsView = [[[MyPinCreationDetailsView alloc] initWithController:self] autorelease];
        [self.pMyPinCreationDetailsView setFrame:[self view].bounds];
        self.view = self.pMyPinCreationDetailsView;

        [self close];
    }
    
    return self;
}

- (void)dealloc
{
    [_pMyPinCreationDetailsView release];
    
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (void) open
{
    if(m_pViewModel->TryAcquireReactorControl())
    {
        [self.pMyPinCreationDetailsView setFullyActive];
    }
}

- (void) close
{
    [self.pMyPinCreationDetailsView setFullyInactive];
}

- (void) handleClosedButtonPressed
{
    m_pViewModel->Close();
    
    ExampleApp::MyPinCreation::MyPinCreationViewStateChangedMessage message(ExampleApp::MyPinCreation::Inactive);
    m_pUiToNativeMessageBus->Publish(message);
}

- (void) handleConfirmButtonPressed:(NSString*) title
                                   :(NSString*) description
                                   :(UIImage*) image
                                   :(BOOL) shouldShare
{
    
    m_pViewModel->Close();
    
    std::string titleAsString = (title != nil && title.length > 0) ? [title UTF8String] : "Untitled Pin";
    std::string descriptionAsString = (description != nil && description.length > 0) ? [description UTF8String] : "No Description";
    std::string imagePathAsString;
    
    Byte* imageDataBytes = NULL;
    size_t imageSize = 0;
    
    if (image)
    {
        NSData* imageData = UIImageJPEGRepresentation(image, 0.9);
        imageDataBytes = (Byte*) [imageData bytes];
        imageSize = [imageData length] / sizeof(Byte);
    }
    
    ExampleApp::MyPinCreation::MyPinCreationViewSavePinMessage message(titleAsString,
                                                                       descriptionAsString,
                                                                       imageDataBytes,
                                                                       imageSize,
                                                                       shouldShare);
    
    m_pUiToNativeMessageBus->Publish(message);
}

@end


