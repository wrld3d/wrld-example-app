// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AppRunner.h"
#include "MenuView.h"

@class PrimaryMenuView;

@interface PrimaryMenuView : MenuView
{
}

- (void)initialiseViews:(size_t)numberOfSections numberOfCells:(size_t)numberOfCells;

@end
