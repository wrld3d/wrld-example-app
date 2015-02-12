// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

@interface UILabelledCheckboxView : UIControl
{
    SEL pClickHandler;
    id pClickHandlerInstance;
}

- (id) initWithParams:(float)checkboxSize
                     :(const char*)checkedAsset
                     :(const char*)uncheckedAsset
                     :(const char*)labelContents
                     :(bool)initiallySelected
                     :(id)clickHandlerInstance
                     :(SEL)clickHandler;

- (bool) isSelected;

- (void) setVisualSelectionState:(bool)selected;

@property (nonatomic, retain) UIButton* pCheckbox;
@property (nonatomic, retain) UILabel* pLabel;

@end