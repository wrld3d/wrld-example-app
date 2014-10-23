// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapViewController.h"
#include "Types.h"
#include "SearchResultOnMapView.h"
#include "ISearchResultOnMapInFocusViewModel.h"
#include "ICallback.h"
#include "SearchResultOnMapViewControllerInterop.h"
#include "SearchResultModel.h"

@interface SearchResultOnMapViewController()<UIGestureRecognizerDelegate>
{
    UITapGestureRecognizer* _tapGestureRecogniser;
}
@end

@implementation SearchResultOnMapViewController

- (id)initWithParams:(ExampleApp::SearchResultOnMap::ISearchResultOnMapInFocusViewModel*)pSearchResultOnMapInFocusViewModel
                    :(ExampleApp::ScreenControlViewModel::IScreenControlViewModel*)pSearchResultPoiScreenControlViewModel
                    :(ExampleApp::Modality::IModalityModel*)pModalityModel
                    :(float)pinDiameter
                    :(float)pixelScale

{
    if(self = [super init])
    {
        m_pinOffset = pinDiameter * 0.75f;
        m_pModalityModel = pModalityModel;
        m_pixelScale = pixelScale;
        m_pSearchResultOnMapInFocusViewModel = pSearchResultOnMapInFocusViewModel;
        m_pInterop = Eegeo_NEW(ExampleApp::SearchResultOnMap::SearchResultOnMapViewControllerInterop)(self,
                                                                                                      *m_pSearchResultOnMapInFocusViewModel,
                                                                                                      *pSearchResultPoiScreenControlViewModel);
        
        self.pSearchResultOnMapView = [[[SearchResultOnMapView alloc] initWithController:self] autorelease];
        [self.pSearchResultOnMapView setFrame:[self view].bounds];
        self.view = self.pSearchResultOnMapView;
        
        if(m_pSearchResultOnMapInFocusViewModel->IsOpen())
        {
            [self open];
        }
        else
        {
            [self close];
        }
        
        _tapGestureRecogniser = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_tapTabGesture:)] autorelease];
        [_tapGestureRecogniser setDelegate:self];
        [self.pSearchResultOnMapView addGestureRecognizer: _tapGestureRecogniser];
    }
    
    return self;
}

- (void)dealloc
{
    [self.pSearchResultOnMapView release];
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (void) open
{
    [self.pSearchResultOnMapView setFullyActive];
    
    [self.pSearchResultOnMapView setLabel
     :m_pSearchResultOnMapInFocusViewModel->GetSearchResultModel().GetTitle()
     :m_pSearchResultOnMapInFocusViewModel->GetSearchResultModel().GetAddress()];
    
    const Eegeo::v2& location = m_pSearchResultOnMapInFocusViewModel->ScreenLocation();
    
    float offsetY = location.y/m_pixelScale - m_pinOffset;
    [self.pSearchResultOnMapView updatePosition:location.x/m_pixelScale :offsetY];
    [self.pSearchResultOnMapView setAlpha: 1.f - m_pModalityModel->GetModality()];
}

- (void) close
{
    [self.pSearchResultOnMapView setFullyInactive];
}

- (void) updateScreenLocation
{
    const Eegeo::v2& location = m_pSearchResultOnMapInFocusViewModel->ScreenLocation();
    float offsetY = location.y/m_pixelScale - m_pinOffset;
    [self.pSearchResultOnMapView updatePosition:location.x/m_pixelScale :offsetY];
}

- (void) handleScreenStateChanged:(float)screenState
{
    if(m_pSearchResultOnMapInFocusViewModel->IsOpen())
    {
        [self.pSearchResultOnMapView setAlpha:screenState];
    }
}

- (void)_tapTabGesture:(UITapGestureRecognizer *)recognizer
{
    if(!m_pModalityModel->IsModalEnabled())
    {
        if(m_pSearchResultOnMapInFocusViewModel->IsOpen())
        {
            m_pSearchResultOnMapInFocusViewModel->SelectFocussedResult();
        }
    }
}

@end


