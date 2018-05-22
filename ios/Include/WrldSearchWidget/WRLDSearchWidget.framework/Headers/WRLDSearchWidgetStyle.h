#pragma once

#import <UIKit/UIKit.h>

/*!
 Configures aspects of the WRLDSearchWidgetView.
 */
@interface WRLDSearchWidgetStyle : NSObject

/*!
 A list of configurable colours used by components of the WRLDSearchWidgetView.
 */
typedef NS_ENUM(NSInteger, WRLDSearchWidgetColorStyleType)
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
    WRLDSearchWidgetStyleMajorDividerColor,
    WRLDSearchWidgetStyleMinorDividerColor,
    WRLDSearchWidgetStyleMenuOptionExpandedColor,
    WRLDSearchWidgetStyleMenuOptionCollapsedColor,
    WRLDSearchWidgetStyleMenuOptionTextExpandedColor,
    WRLDSearchWidgetStyleMenuOptionTextCollapsedColor,
    WRLDSearchWidgetStyleMenuOptionTextHoverColor,
    WRLDSearchWidgetStyleMenuOptionHoverColor,
    WRLDSearchWidgetStyleMenuChildOptionHoverColor,
    WRLDSearchWidgetStyleMenuIconColor,
    WRLDSearchWidgetNumberOfColorStyles
};

/*!
 A list of configurable number values used by components of the WRLDSearchWidgetView.
 */
typedef NS_ENUM(NSInteger, WRLDSearchWidgetNumberStyleType)
{
    WRLDSearchWidgetStyleElevation,
    WRLDSearchWidgetMaxSuggestionsPerProvider,
    WRLDSearchWidgetMaxCollapsedSearchResults,
    WRLDSearchWidgetMaxExpandedSearchResults,
    WRLDSearchWidgetNumberOfNumberStyles
};

/*!
 An event to be invoked when one of the WRLDSearchWidgetColorStyleTypes are modified and the style applied.
 */
typedef void (^ApplyColorEvent) (UIColor* color);

/*!
 An event to be invoked when one of the WRLDSearchWidgetNumberStyleTypes are modified and the style applied.
 */
typedef void (^ApplyNumberEvent) (CGFloat number);

/*!
 Tells the WRLDSearchWidgetStyle to use a color value.
 Does not apply changes - call apply to update the WRLDSearchWidgetView.
 @param color the UIColor color value to use for the style.
 @param style the WRLDSearchWidgetColorStyleType to apply the color to.
 */
- (void) usesColor: (UIColor *) color forStyle: (WRLDSearchWidgetColorStyleType) style;

/*!
 Fetches the curretnly applied value for a color style.  Does not reflect unapplied changes to the style.
 @param style the WRLDSearchWidgetColorStyleType to obtain the color value for.
 @return the currently applied color value.
 */
- (UIColor *) colorForStyle: (WRLDSearchWidgetColorStyleType) style;

/*!
 Register a method to be called when a WRLDSearchWidgetColorStyleType change is applied.
 The method is invoked immediately with the currently applied value.
 The method is not invoked if the applied value is not different from the previous apply call.
 @param event A method matching the signature of ApplyColorEvent to be invoked when the style changes.
 @param style A WRLDSearchWidgetColorStyleType to observe changes to.
 */
- (void) call: (ApplyColorEvent) event toApplyColorStyle: (WRLDSearchWidgetColorStyleType) style;

/*!
 Tells the WRLDSearchWidgetStyle to use a number value.
 Does not apply changes - call apply to update the WRLDSearchWidgetView.
 @param number the CGFloat value to use for the style.
 @param style the WRLDSearchWidgetNumberStyleType to apply the number to.
 */
- (void) usesNumber: (CGFloat) number forStyle: (WRLDSearchWidgetNumberStyleType) style;

/*!
 Fetches the curretnly applied value for a number style.  Does not reflect unapplied changes to the style.
 @param style the WRLDSearchWidgetNumberStyleType to obtain the number value for.
 @return the currently applied CGFloat value.
 */
- (CGFloat) numberForStyle: (WRLDSearchWidgetNumberStyleType) style;

/*!
 Tells the WRLDSearchWidgetStyle to use a number value.
 Does not apply changes - call apply to update the WRLDSearchWidgetView.
 The method is not invoked if the applied value is not different from the previous apply call.
 @param event the CGFloat value to use for the style.
 @param style the WRLDSearchWidgetNumberStyleType to apply the number to.
 */
- (void) call: (ApplyNumberEvent) event toApplyNumberStyle: (WRLDSearchWidgetNumberStyleType) style;

/*!
 Applies changes to the style from call: toApplyColorStyle and call: toApplyNumberStyle.
 Registered methods for styles are only invoked if the unapplied style is different to the applied style.
 */
- (void) apply;

@end
