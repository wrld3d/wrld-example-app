// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "IMenuView.h"
#include "CustomTableRowSelectionDelegate.h"

@class MenuView;
@class MenuViewInterop;
@class CustomTableView;

@interface CustomTableDataProvider : UITableViewController<UITableViewDelegate, UITableViewDataSource>
{
    MenuView* m_pView;
    ExampleApp::Menu::View::TSections m_currentSections;
    std::vector<std::string> m_previousTags;
}

- (id)initWithParams:(MenuView*)view
                    :(NSMutableDictionary*)tableViewMap;

- (void)collapseAll;

- (CGAffineTransform)computeOpenableArrowTransform:(float)degrees;

- (void)showOpenableArrowClosed:(UITableViewCell *)cell;

- (void)showOpenableArrowOpen:(UITableViewCell *)cell;

- (void)updateMenuSections:(ExampleApp::Menu::View::TSections*)sections;

- (float)getRealHeightForTable:(CustomTableView*)customTableView;

@property (nonatomic, retain) UIImage* pOpenableMenuArrow;
@property (nonatomic, retain) id <CustomTableRowSelectionDelegate> rowSelectionDelegate;

@end;