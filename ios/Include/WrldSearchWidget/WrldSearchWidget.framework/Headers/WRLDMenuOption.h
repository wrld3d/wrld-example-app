#pragma once

#import <Foundation/Foundation.h>

@class WRLDMenuChild;

NS_ASSUME_NONNULL_BEGIN

/*!
 A WRLDMenuOption is a menu option that is always visible.  They can be selected on their own or contain child objects that are only visible when the WRLDMenuOption is expanded.
 WRLDMenuOptions are contained within WRLDMenuGroups in the menu heirarchy.
 */
@interface WRLDMenuOption : NSObject

/*!
 @return NSString text to be displayed in the search menu for this option.
 */
@property (nonatomic, copy, readonly) NSString* text;

/*!
 @return context NSObject containing additional context to use when the menu option is selected.  Can be nil if the menu option has no context.
 */
@property (nonatomic, copy, readonly) NSObject* _Nullable context;

/*!
 Constructor.
 @param text NSString text to be displayed in the search menu for this option.
 @param context NSObject containing additional context for use when the option is selected.  Can be nil.
 */
- (instancetype) initWithText: (NSString*) text
                      context: (nullable NSObject*) context;

/*!
 Add a child item to the bottom of the option.
 @parm WRLDMenuChild item to display when the menu is expanded.
 */
- (void) addChild: (WRLDMenuChild*) child;

/*!
 Add a new child item to the bottom of the option using the parameters to generate it.
 @parm text NSString text to display for the child item.
 @parm icon NSString that resolves to an icon to be displayed next to the text.  Can be nil if there is no icon to display.
 @parm context NSObject containing additional context for use when the child item is selected.  Can be nil.
 */
- (void) addChild: (NSString*) text
             icon: (nullable NSString*) icon
          context: (nullable NSObject*) context;

/*!
 Remove a child item from the option.
 @param option WRLDMenuChild item to remove.
 */
- (void) removeChild: (WRLDMenuChild*) option;

/*!
 Insert a child item to be displayed when the option is expanded.
 @param option WRLDMenuChild child item to insert.
 @param index NSUInteger position within the option to insert the child item.
 */
- (void) insertChild: (WRLDMenuChild*) option
             atIndex: (NSUInteger) index;

/*!
 Remove a child from the items displayed when the option is expanded.
 @param index NSUInteger position of the item to remove.
 */
- (void) removeChildAtIndex: (NSUInteger) index;

/*!
 Remove all children from an option.
 */
- (void) removeAllChildren;

@end

NS_ASSUME_NONNULL_END

