// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

#include "MenuView.h"
#include "SettingsMenuViewIncludes.h"

@interface SettingsMenuView : MenuView<UITextFieldDelegate>
{
    ExampleApp::SettingsMenu::View::SettingsMenuViewInterop* m_pSettingsMenuInterop;

    float m_titleContainerX;
    float m_titleContainerY;
    float m_titleContainerWidth;
    float m_titleContainerHeight;
}

- (void)initialiseViews:(size_t)numberOfSections numberOfCells:(size_t)numberOfCells;

- (ExampleApp::SettingsMenu::View::SettingsMenuViewInterop*) getSettingsMenuInterop;

@property (nonatomic, retain) UILabel* pTitleLabel;
@property (nonatomic, retain) UIView* pTitleContainer;

@end
