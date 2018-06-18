// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultPoiViewIncludes.h"
#include "Types.h"
#include "AppRunner.h"
#include "SearchResultModel.h"
#include "SearchResultPoi.h"
#include "SearchResultPoiView.h"

#include <vector>

#import <UIKit/UIKit.h>

@interface SearchResultPoiViewContainer : UIView
{
    UIView<SearchResultPoiView>* m_pCurrentActiveVendorView;
    ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* m_pInterop;
}

- (id) initWithDirectionsButton: (BOOL) showDirectionsButton;

- (ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*) getInterop;

- (void) open:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned;

- (void) close;

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;


@end
