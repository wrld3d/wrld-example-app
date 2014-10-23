// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AppRunner.h"
#include "MenuViewController.h"
#include "MenuView.h"

@class SearchResultMenuView;

@interface SearchResultMenuView : MenuView
{
    __weak MenuViewController* m_pController;
}

- (id) setController:(MenuViewController *)controller;

- (void) updateViewForQuery:(std::string)searchText :(bool)queryPending :(size_t)numResults;

@property (nonatomic, retain) UIView* pCategory;
@property (nonatomic, retain) UILabel* pHeading;
@property (nonatomic, retain) UIActivityIndicatorView* pSpinner;
@property (nonatomic, retain) UILabel* pResultsCount;
@property (nonatomic, retain) UIButton* pClearResults;

@end
