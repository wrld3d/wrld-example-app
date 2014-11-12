// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "SearchResultPoiView.h"
#include "SearchResultModel.h"
#include "ISearchResultPoiViewModel.h"

namespace ExampleApp
{
	namespace SearchResultPoi
	{
		class SearchResultPoiViewControllerInterop;
	}
}

@interface SearchResultPoiViewController : UIViewController
{
	ExampleApp::SearchResultPoi::ISearchResultPoiViewModel* m_pSearchResultPoiViewModel;
	ExampleApp::SearchResultPoi::SearchResultPoiViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(ExampleApp::SearchResultPoi::ISearchResultPoiViewModel*)pSearchResultPoiViewModel;

- (void) openWithModel:(const ExampleApp::Search::SearchResultModel&)searchResultModel;

- (void) close;

@property (nonatomic, retain) SearchResultPoiView* pSearchResultPoiView;

@end
