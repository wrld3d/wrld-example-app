// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "Menu.h"
#include "MenuViewControllerInterop.h"
#include "Modality.h"
#include "UpdateProtocol.h"

@class MenuViewController;
@class MenuView;

FOUNDATION_EXPORT NSInteger const SubItemCellShadowViewTag;
FOUNDATION_EXPORT NSInteger const SubItemCellShadowFlippedViewTag;

@interface MenuViewController : UITableViewController<UIGestureRecognizerDelegate, UITableViewDelegate, UITableViewDataSource, UpdateProtocol>
{
    ExampleApp::Menu::IMenuModel* m_pMenuModel;
    ExampleApp::Menu::IMenuViewModel* m_pMenuViewModel;
    ExampleApp::Modality::IModalityModel* m_pModalityModel;
    ExampleApp::MenuView::MenuViewControllerInterop<ExampleApp::Menu::MenuItemModel, MenuViewController>* m_pInterop;
    bool m_isRightMenu;
}

- (id)initWithParams:(ExampleApp::Menu::IMenuModel *)pMenuModel
                    :(ExampleApp::Menu::IMenuViewModel *)pMenuViewModel
                    :(MenuView*)pMenuView
                    :(ExampleApp::Modality::IModalityModel*)pModalityModel
                    :(bool)isRightMenu;

- (void)handleItemAdded;

- (void)handleItemRemoved;

- (void) handleScreenStateChanged:(float)onScreenState;

- (void) handleOpenStateChanged:(float)openState;

- (void) handleViewOpenCompleted;

- (void) handleViewCloseCompleted;

- (void) handleDraggingViewInProgress:(float)normalisedDragState;

- (void) dragTabGesture:(UIPanGestureRecognizer *)recognizer;

- (void) tapTabGesture:(UITapGestureRecognizer *)recognizer;

- (CGAffineTransform)computeOpenableArrowTransform:(float)degrees;

- (void)showOpenableArrowClosed:(UITableViewCell *)cell;

- (void)showOpenableArrowOpen:(UITableViewCell *)cell;

@property (nonatomic, retain) MenuView* pMenuView;
@property (nonatomic, retain) UIImage* pSubItemShadow;
@property (nonatomic, retain) UIImage* pSubItemShadowFlipped;
@property (nonatomic, retain) UIImage* pOpenableMenuArrow;

@end
