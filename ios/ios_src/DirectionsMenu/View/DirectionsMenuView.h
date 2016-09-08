// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

#include "MenuView.h"
#include "DirectionsMenuViewIncludes.h"

@class DirectionsMenuView;

@interface DirectionsMenuView : MenuView<UIScrollViewDelegate>
{
    int resultCount;
}

- (id)initWithParams:(float)width
                    :(float)height
                    :(float)pixelScale;

- (ExampleApp::DirectionsMenu::View::DirectionsMenuViewInterop*) getDirectionsMenuInterop;

- (void) collapseAll;

@property (nonatomic, retain) UIScrollView* pSearchResultsTableContainerView;

@end
