// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultPoiViewController.h"
#include "Types.h"
#include "SearchResultPoiView.h"
#include "ISearchResultPoiViewModel.h"
#include "ICallback.h"
#include "SearchResultPoiViewControllerInterop.h"

@interface SearchResultPoiViewController()<UIGestureRecognizerDelegate>
{
	UITapGestureRecognizer* _tapGestureRecogniser;
}
@end

@implementation SearchResultPoiViewController

- (id)initWithParams:(ExampleApp::SearchResultPoi::ISearchResultPoiViewModel*)pSearchResultPoiViewModel;
{
	if(self = [super init])
	{
		m_pSearchResultPoiViewModel = pSearchResultPoiViewModel;
		m_pInterop = Eegeo_NEW(ExampleApp::SearchResultPoi::SearchResultPoiViewControllerInterop)(self, *m_pSearchResultPoiViewModel);

		self.pSearchResultPoiView = [[[SearchResultPoiView alloc] initWithController:self] autorelease];
		[self.pSearchResultPoiView setFrame:[self view].bounds];
		self.view = self.pSearchResultPoiView;

		if(m_pSearchResultPoiViewModel->IsOpen())
		{
			[self openWithModel:m_pSearchResultPoiViewModel->GetSearchResultModel()];
		}

		_tapGestureRecogniser = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_tapTabGesture:)] autorelease];
		[_tapGestureRecogniser setDelegate:self];
		[[self.pSearchResultPoiView pCloseButton] addGestureRecognizer: _tapGestureRecogniser];
	}

	return self;
}

- (void)dealloc
{
	[_pSearchResultPoiView release];

	Eegeo_DELETE m_pInterop;
	[super dealloc];
}

- (void) openWithModel:(const ExampleApp::Search::SearchResultModel&)searchResultModel
{
	if(!m_pSearchResultPoiViewModel->TryAcquireReactorControl())
	{
		m_pSearchResultPoiViewModel->Close();
		return;
	}

	[self.pSearchResultPoiView setFullyActive];
	[self.pSearchResultPoiView setContent:&searchResultModel];
}

- (void) close
{
	[self.pSearchResultPoiView setFullyInactive];
}

- (void)_tapTabGesture:(UITapGestureRecognizer *)recognizer
{
	m_pSearchResultPoiViewModel->Close();
}

@end


