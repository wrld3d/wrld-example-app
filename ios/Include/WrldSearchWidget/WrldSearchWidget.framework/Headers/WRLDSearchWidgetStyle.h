#pragma once

#import <UIKit/UIKit.h>

@interface WRLDSearchWidgetStyle : NSObject

typedef NS_ENUM(NSInteger, WRLDSearchWidgetStyleType)
{
    WRLDSearchWidgetStylePrimaryColor,
    WRLDSearchWidgetStyleSecondaryColor,
    WRLDSearchWidgetStyleSearchBarColor,
    WRLDSearchWidgetStyleResultBackgroundColor,
    WRLDSearchWidgetStyleResultSelectedColor,
    WRLDSearchWidgetStyleTextPrimaryColor,
    WRLDSearchWidgetStyleTextSecondaryColor,
    WRLDSearchWidgetStyleLinkColor,
    WRLDSearchWidgetStyleWarningColor,
    WRLDSearchWidgetStyleDividerColor,
    WRLDSearchWidgetStyleMenuGroupExpandedColor,
    WRLDSearchWidgetStyleMenuGroupCollapsedColor,
    WRLDSearchWidgetStyleMenuGroupTextExpandedColor,
    WRLDSearchWidgetStyleMenuGroupTextCollapsedColor,
    WRLDSearchWidgetStyleMenuGroupTextHoverColor,
    WRLDSearchWidgetStyleMenuHoverColor,
    WRLDSearchWidgetStyleMenuIconColor,
    WrldSearchWidgetNumberOfStyles
};

typedef void (^ApplyColorEvent) (UIColor * color);

- (void) usesColor: (UIColor *) color forStyle: (WRLDSearchWidgetStyleType) style;

- (UIColor *) colorForStyle: (WRLDSearchWidgetStyleType) style;

- (void) call: (ApplyColorEvent) event toApply: (WRLDSearchWidgetStyleType) style;

- (void) apply;

@end
