// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AppRunner.h"
#include "MenuViewController.h"
#include "MenuView.h"

@class SecondaryMenuView;

@interface SecondaryMenuView : MenuView
{
	__weak MenuViewController* m_pController;

	float m_searchBoxContainerX;
	float m_searchBoxContainerY;
	float m_searchBoxContainerWidth;
	float m_searchBoxContainerHeight;
}

- (id) setController:(MenuViewController *)controller;

@property (nonatomic, retain) UITextField* pSearchEditBox;
@property (nonatomic, retain) UIView* pSearchEditBoxContainer;

@end
