// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "CompassViewController.h"
#include "CompassView.h"
#include "CompassViewModel.h"
#include "CompassViewControllerInterop.h"
#include "ScreenProperties.h"

@interface CompassViewController()<UIGestureRecognizerDelegate>
{
    UITapGestureRecognizer* _tapGestureRecogniser;
}
@end

@implementation CompassViewController

- (id)initWithParams:(ExampleApp::Compass::ICompassModel*)pModel
                    :(ExampleApp::Compass::ICompassViewModel*)pViewModel
                    :(const Eegeo::Rendering::ScreenProperties*)pScreenProperties

{
    if(self = [super init])
    {
        self.pCompassView = [[[CompassView alloc] initWithParams
                             :self
                             :pScreenProperties->GetScreenWidth()
                             :pScreenProperties->GetScreenHeight()
                             :pScreenProperties->GetPixelScale()] autorelease];
        
        self.view = self.pCompassView;
        
        m_pModel = pModel;
        m_pViewModel = pViewModel;
        m_pInterop = Eegeo_NEW(ExampleApp::Compass::CompassViewControllerInterop)(self, *m_pModel, *m_pViewModel);
        
        _tapGestureRecogniser = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_tapTabGesture:)] autorelease];
        [_tapGestureRecogniser setDelegate:self];
        [self.pCompassView addGestureRecognizer: _tapGestureRecogniser];
        
        [self.pCompassView setOnScreenStateToIntermediateValue:m_pViewModel->OnScreenState()];
        
    }
    
    return self;
}

- (void)dealloc
{
    [self.pCompassView release];
    
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (void) handleGpsModeChanged
{
    switch(m_pModel->GetGpsMode())
    {
        case ExampleApp::Compass::GpsMode::GpsDisabled:
        {
            [self.pCompassView showGpsDisabledView];
        }break;
            
        case ExampleApp::Compass::GpsMode::GpsFollow:
        {
            [self.pCompassView showGpsFollowView];
        }break;
            
        case ExampleApp::Compass::GpsMode::GpsCompassMode:
        {
            [self.pCompassView showGpsCompassModeView];
        }break;
            
        default:
        {
            Eegeo_ASSERT(false, "Invalid GPS mode\n");
        }break;
    }
}

- (void) updateHeading:(float)angleRadians
{
    [self.pCompassView updateHeading: angleRadians];
}

- (void) handleScreenStateChanged:(float)onScreenState
{
    if(m_pViewModel->IsFullyOffScreen())
    {
        [self.pCompassView setFullyOffScreen];
    }
    else if(m_pViewModel->IsFullyOnScreen())
    {
        [self.pCompassView setFullyOnScreen];
    }
    else
    {
        [self.pCompassView setOnScreenStateToIntermediateValue:m_pViewModel->OnScreenState()];
    }
}

- (void)_tapTabGesture:(UITapGestureRecognizer *)recognizer
{
    m_pModel->CycleToNextGpsMode();
}


@end
