// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "PoiCreationConfirmationViewController.h"
#include "PoiCreationConfirmationView.h"
#include "PoiCreationConfirmationViewModel.h"
#include "PoiCreationConfirmationViewControllerInterop.h"
#include "ScreenProperties.h"
#include "IPoiCreationDetailsViewModel.h"

@implementation PoiCreationConfirmationViewController

- (id)initWithParams:(ExampleApp::PoiCreation::IPoiCreationModel*)pModel
                    :(ExampleApp::PoiCreation::IPoiCreationConfirmationViewModel*)pViewModel
                    :(ExampleApp::PoiCreation::IPoiCreationCompositeViewModel*)pCompositeViewModel
                    :(ExampleApp::PoiCreationDetails::IPoiCreationDetailsViewModel*)pDetailsViewModel
                    :(const Eegeo::Rendering::ScreenProperties*)pScreenProperties

{
    if(self = [super init])
    {
        self.pPoiCreationConfirmationView = [[[PoiCreationConfirmationView alloc] initWithParams :self
                                                                                                 :pScreenProperties->GetScreenWidth()
                                                                                                 :pScreenProperties->GetScreenHeight()
                                                                                                 :pScreenProperties->GetPixelScale()] autorelease];
        
        m_pModel = pModel;
        m_pViewModel = pViewModel;
        m_pDetailsViewModel = pDetailsViewModel;
        m_pInterop = Eegeo_NEW(ExampleApp::PoiCreation::PoiCreationConfirmationViewControllerInterop)(self, *m_pModel, *m_pViewModel, *pCompositeViewModel);
        
        [self.pPoiCreationConfirmationView setOnScreenStateToIntermediateValue:m_pViewModel->OnScreenState()];
        
    }
    
    return self;
}

- (void)dealloc
{
    [self.pPoiCreationConfirmationView release];
    
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (void) handleScreenStateChanged:(float)onScreenState
{
    if(m_pViewModel->IsFullyOffScreen())
    {
        [self.pPoiCreationConfirmationView setFullyOffScreen];
    }
    else if(m_pViewModel->IsFullyOnScreen())
    {
        [self.pPoiCreationConfirmationView setFullyOnScreen];
    }
    else
    {
        [self.pPoiCreationConfirmationView setOnScreenStateToIntermediateValue:m_pViewModel->OnScreenState()];
    }
}

- (void) handleCloseButtonSelected
{
    m_pModel->SetCreationStage(ExampleApp::PoiCreation::Inactive);
}

- (void) handleConfirmButtonSelected
{
    m_pModel->SetCreationStage(ExampleApp::PoiCreation::Details);
    m_pViewModel->RemoveFromScreen();
    m_pDetailsViewModel->Open();
}

@end
