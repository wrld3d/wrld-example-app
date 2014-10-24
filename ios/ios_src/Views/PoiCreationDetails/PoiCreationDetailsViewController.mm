// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationDetailsViewController.h"
#include "PoiCreationDetailsViewControllerInterop.h"
#include "PoiCreationDetailsView.h"
#include "PoiCreationDetailsViewModel.h"
#include "IPoiCreationModel.h"
#include <string>

@implementation PoiCreationDetailsViewController

- (id)initWithParams:(ExampleApp::PoiCreation::IPoiCreationModel*)pModel
                    :(ExampleApp::PoiCreationDetails::IPoiCreationDetailsViewModel*)pViewModel
{
    if(self = [super init])
    {
        m_pModel = pModel;
        m_pViewModel = pViewModel;
        m_pInterop = Eegeo_NEW(ExampleApp::PoiCreationDetails::PoiCreationDetailsViewControllerInterop)(self, *m_pViewModel);
        
        self.pPoiCreationDetailsView = [[[PoiCreationDetailsView alloc] initWithController:self] autorelease];
        [self.pPoiCreationDetailsView setFrame:[self view].bounds];
        self.view = self.pPoiCreationDetailsView;

        [self close];
    }
    
    return self;
}

- (void)dealloc
{
    [_pPoiCreationDetailsView release];
    
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (void) open
{
    if(m_pViewModel->TryAcquireReactorControl())
    {
        [self.pPoiCreationDetailsView setFullyActive];
    }
}

- (void) close
{
    [self.pPoiCreationDetailsView setFullyInactive];
}

- (void) handleClosedButtonPressed
{
    m_pModel->SetCreationStage(ExampleApp::PoiCreation::Inactive);
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


