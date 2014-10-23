// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "SearchResultOnMapView.h"
#include "SearchResultModel.h"
#include "ISearchResultOnMapInFocusViewModel.h"
#include "IScreenControlViewModel.h"
#include "IModalityModel.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        class SearchResultOnMapViewControllerInterop;
    }
}

@interface SearchResultOnMapViewController : UIViewController
{
    ExampleApp::SearchResultOnMap::ISearchResultOnMapInFocusViewModel* m_pSearchResultOnMapInFocusViewModel;
    ExampleApp::SearchResultOnMap::SearchResultOnMapViewControllerInterop* m_pInterop;
    ExampleApp::Modality::IModalityModel* m_pModalityModel;
    float m_pinOffset;
    float m_pixelScale;
}

- (id)initWithParams:(ExampleApp::SearchResultOnMap::ISearchResultOnMapInFocusViewModel*)pSearchResultOnMapInFocusViewModel
                    :(ExampleApp::ScreenControlViewModel::IScreenControlViewModel*)pSearchResultPoiScreenControlViewModel
                    :(ExampleApp::Modality::IModalityModel*)pModalityModel
                    :(float)pinDiameter
                    :(float)pixelScale;

- (void) open;

- (void) close;

- (void) updateScreenLocation;

- (void) handleScreenStateChanged:(float)screenState;

@property (nonatomic, retain) SearchResultOnMapView* pSearchResultOnMapView;

@end
