// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AppRunner.h"
#include "MenuViewController.h"
#include "MenuView.h"

@class PrimaryMenuView;

@interface PrimaryMenuView : MenuView 
{
    __weak MenuViewController* m_pController;
}

- (id) setController:(MenuViewController *)controller;


@end
