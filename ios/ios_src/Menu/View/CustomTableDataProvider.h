// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "IMenuView.h"

@class MenuView;
@class MenuViewInterop;

@interface CustomTableDataProvider : UITableViewController<UITableViewDelegate, UITableViewDataSource>
{
    MenuView* m_pView;
    ExampleApp::Menu::View::TSections m_currentSections;
}

- (id)initWithParams:(MenuView*) view;

- (size_t)getNumberOfSections;

- (size_t)getTotalNumberOfCellsInTableView;

- (void)collapseAll;

- (CGAffineTransform)computeOpenableArrowTransform:(float)degrees;

- (void)showOpenableArrowClosed:(UITableViewCell *)cell;

- (void)showOpenableArrowOpen:(UITableViewCell *)cell;

- (void)updateMenuSections:(ExampleApp::Menu::View::TSections*)sections;

- (float)getRealTableHeight;

@property (nonatomic, retain) UIImage* pOpenableMenuArrow;

@end;