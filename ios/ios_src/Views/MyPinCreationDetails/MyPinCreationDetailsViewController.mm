// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationDetailsViewController.h"
#include "MyPinCreationDetailsViewControllerInterop.h"
#include "MyPinCreationDetailsView.h"
#include "MyPinCreationDetailsViewModel.h"
#include "IMyPinCreationModel.h"
#include <string>

@implementation MyPinCreationDetailsViewController

- (id)initWithParams:(ExampleApp::MyPinCreation::IMyPinCreationModel*)pModel
                    :(ExampleApp::MyPinCreationDetails::IMyPinCreationDetailsViewModel*)pViewModel
{
    if(self = [super init])
    {
        m_pModel = pModel;
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
    m_pModel->SetCreationStage(ExampleApp::MyPinCreation::Inactive);
    m_pViewModel->Close();
}

- (void) handleConfirmButtonPressed:(NSString*) title
                                   :(NSString*) description
                                   :(UIImage*) image
                                   :(BOOL) shouldShare
{
    std::string titleAsString = title ? [title UTF8String] : "";
    std::string descriptionAsString = description ? [description UTF8String] : "";
    std::string imagePathAsString;
    
    Byte* imageDataBytes = NULL;
    size_t imageSize = 0;
    
    if (image)
    {
        NSData* imageData = UIImageJPEGRepresentation(image, 0.9);
        imageDataBytes = (Byte*) [imageData bytes];
        imageSize = [imageData length] / sizeof(Byte);
    }

    m_pModel->SavePoi(titleAsString,
                      descriptionAsString,
                      imageDataBytes,
                      imageSize,
                      shouldShare);
    
    m_pViewModel->Close();
}

@end


