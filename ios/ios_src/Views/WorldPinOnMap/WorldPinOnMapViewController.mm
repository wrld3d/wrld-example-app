// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinOnMapViewController.h"
#include "Types.h"
#include "WorldPinOnMapView.h"
#include "IWorldPinInFocusViewModel.h"
#include "ICallback.h"
#include "WorldPinOnMapViewControllerInterop.h"
#include "WorldPinsInFocusModel.h"

@interface WorldPinOnMapViewController()<UIGestureRecognizerDelegate>
{
	UITapGestureRecognizer* _tapGestureRecogniser;
}
@end

@implementation WorldPinOnMapViewController

- (id)initWithParams:(ExampleApp::WorldPins::IWorldPinInFocusViewModel*)pWorldPinInFocusViewModel
    :(ExampleApp::ScreenControlViewModel::IScreenControlViewModel*)pWorldPinOnMapInFocusScreenControlViewModel
    :(ExampleApp::Modality::IModalityModel*)pModalityModel
    :(float)pinDiameter
    :(float)pixelScale

{
	if(self = [super init])
	{
		m_pinOffset = pinDiameter * 0.75f;
		m_pModalityModel = pModalityModel;
		m_pixelScale = pixelScale;
		m_pWorldPinInFocusViewModel = pWorldPinInFocusViewModel;
		m_pInterop = Eegeo_NEW(ExampleApp::WorldPins::WorldPinOnMapViewControllerInterop)(self,
                                                                                          *m_pWorldPinInFocusViewModel,
                                                                                          *pWorldPinOnMapInFocusScreenControlViewModel);

		self.pWorldPinOnMapView = [[[WorldPinOnMapView alloc] initWithController:self] autorelease];
		[self.pWorldPinOnMapView setFrame:[self view].bounds];
		self.view = self.pWorldPinOnMapView;

		if(m_pWorldPinInFocusViewModel->IsOpen())
		{
			[self open];
		}
		else
		{
			[self close];
		}

		_tapGestureRecogniser = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_tapTabGesture:)] autorelease];
		[_tapGestureRecogniser setDelegate:self];
		[self.pWorldPinOnMapView addGestureRecognizer: _tapGestureRecogniser];
	}

	return self;
}

- (void)dealloc
{
	[self.pWorldPinOnMapView release];
	Eegeo_DELETE m_pInterop;
	[super dealloc];
}

- (void) open

{
	[self.pWorldPinOnMapView setFullyActive];

	[self.pWorldPinOnMapView setLabel
	 :m_pWorldPinInFocusViewModel->GetWorldPinsInFocusModel().GetTitle()
	 :m_pWorldPinInFocusViewModel->GetWorldPinsInFocusModel().GetSubtitle()];

	const Eegeo::v2& location = m_pWorldPinInFocusViewModel->ScreenLocation();

	float offsetY = location.y/m_pixelScale - m_pinOffset;
	[self.pWorldPinOnMapView updatePosition:location.x/m_pixelScale :offsetY];
	[self.pWorldPinOnMapView setAlpha: 1.f - m_pModalityModel->GetModality()];
}

- (void) close
{
	[self.pWorldPinOnMapView setFullyInactive];
}

- (void) updateScreenLocation
{
	const Eegeo::v2& location = m_pWorldPinInFocusViewModel->ScreenLocation();
	float offsetY = location.y/m_pixelScale - m_pinOffset;
	[self.pWorldPinOnMapView updatePosition:location.x/m_pixelScale :offsetY];
}

- (void) handleScreenStateChanged:(float)screenState
{
	if(m_pWorldPinInFocusViewModel->IsOpen())
	{
		[self.pWorldPinOnMapView setAlpha:screenState];
	}
}

- (void)_tapTabGesture:(UITapGestureRecognizer *)recognizer
{
	if(!m_pModalityModel->IsModalEnabled())
	{
		if(m_pWorldPinInFocusViewModel->IsOpen())
		{
			m_pWorldPinInFocusViewModel->SelectFocussedResult();
		}
	}
}

@end


