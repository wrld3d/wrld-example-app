// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AppRunner.h"
#include "MenuView.h"

@class SecondaryMenuView;

@interface SecondaryMenuView : MenuView<UITextFieldDelegate>
{
    ExampleApp::SecondaryMenu::View::SecondaryMenuViewInterop* m_pSecondaryMenuInterop;

    bool m_keyboardActive;
    bool m_returnPressed;

    float m_searchBoxContainerX;
    float m_searchBoxContainerY;
    float m_searchBoxContainerWidth;
    float m_searchBoxContainerHeight;
}

- (void)initialiseViews:(size_t)numberOfSections numberOfCells:(size_t)numberOfCells;

- (ExampleApp::SecondaryMenu::View::SecondaryMenuViewInterop*) getSecondaryMenuInterop;

- (void) enableEdit;

- (void) disableEdit;

- (void) removeSeachKeyboard;

@property (nonatomic, retain) UITextField* pSearchEditBox;
@property (nonatomic, retain) UIView* pSearchEditBoxContainer;

@end
