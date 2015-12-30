// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

#include "MenuView.h"
#include "SettingsMenuViewIncludes.h"

@interface SettingsMenuView : MenuView<UITextFieldDelegate>
{
    
}

- (ExampleApp::SettingsMenu::View::SettingsMenuViewInterop*) getSettingsMenuInterop;

@end
