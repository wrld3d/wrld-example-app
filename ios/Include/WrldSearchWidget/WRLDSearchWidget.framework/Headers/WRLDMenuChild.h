#pragma once

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 A WRLDMenuChild is a submenu item underneath a WRLDMenuOption.  A WRLDMenuChild is only visible when the WRLDMenuOption that contains it is expanded.
 */
@interface WRLDMenuChild : NSObject

/*!
 @return NSString text to be displayed in the search menu for this option.
 */
@property (nonatomic, copy, readonly) NSString* text;

/*!
 @return NSString object that resolves to an icon to be displayed next to the text.  Can be nil if the menu option has no icon.
 */
@property (nonatomic, copy, readonly) NSString* _Nullable icon;

/*!
 When the WRLDMenuChild is selected, the context is passed to objects that are registered with the WRLDMenuObserver.
 @return context NSObject containing information relevant to the menu item.  Can be nil if the menu item has no context.
 */
@property (nonatomic, copy, readonly) NSObject* _Nullable context;

/*!
 Creates a new instance of a WRLDChildMenu.
 @param text NSString to be displayed in the search menu for this item.
 @param icon NSString used to lookup an icon for this item.
 @param context NSObject information relevant to the menu item.  Can be null if the menu item has no context.
 */
- (instancetype)initWithText:(NSString*) text
                        icon:(nullable NSString*) icon
                     context:(nullable NSObject*) context;

@end

NS_ASSUME_NONNULL_END
