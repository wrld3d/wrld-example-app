// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "PoiCreationButtonViewController.h"
#include "PoiCreationButtonView.h"
#include "PoiCreationButtonViewModel.h"
#include "PoiCreationButtonViewControllerInterop.h"
#include "ScreenProperties.h"

@implementation PoiCreationButtonViewController

- (id)initWithParams:(ExampleApp::PoiCreation::IPoiCreationModel*)pModel
                    :(ExampleApp::PoiCreation::IPoiCreationButtonViewModel*)pViewModel
                    :(const Eegeo::Rendering::ScreenProperties*)pScreenProperties

{
    if(self = [super init])
    {
        self.pPoiCreationButtonView = [[[PoiCreationButtonView alloc] initWithParams :self
                                                                                     :pScreenProperties->GetScreenWidth()
                                                                                     :pScreenProperties->GetScreenHeight()
                                                                                     :pScreenProperties->GetPixelScale()] autorelease];
        
        m_pModel = pModel;
        m_pViewModel = pViewModel;
        m_pInterop = Eegeo_NEW(ExampleApp::PoiCreation::PoiCreationButtonViewControllerInterop)(self, *m_pModel, *m_pViewModel);

        [self.pPoiCreationButtonView setOnScreenStateToIntermediateValue:m_pViewModel->OnScreenState()];
        
    }
    
    return self;
}

- (void)dealloc
{
    [self.pPoiCreationButtonView release];
    
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (void) handleScreenStateChanged:(float)onScreenState
{

    [self.pPoiCreationButtonView shouldOffsetButton: m_pViewModel->ShouldOffsetViewButton()];
    
    if(m_pViewModel->IsFullyOffScreen())
    {
        [self.pPoiCreationButtonView setFullyOffScreen];
    }
    else if(m_pViewModel->IsFullyOnScreen())
    {
        [self.pPoiCreationButtonView setFullyOnScreen];
    }
    else
    {
        [self.pPoiCreationButtonView setOnScreenStateToIntermediateValue:m_pViewModel->OnScreenState()];
    }
}

- (void) setSelected:(BOOL)selected
{
    m_pModel->SetCreationStage(ExampleApp::PoiCreation::Ring);
}


@end
