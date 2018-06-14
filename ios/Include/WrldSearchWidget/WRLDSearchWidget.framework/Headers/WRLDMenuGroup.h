#pragma once

#import <Foundation/Foundation.h>

@class WRLDMenuOption;

NS_ASSUME_NONNULL_BEGIN

/*!
 A WRLDMenuGroup is a collection of menu content that is visually separated into its own section within the menu.
 A WRLDMenuGroup contains WRLDMenuOptions but cannot be interacted with on their own.
 */
@interface WRLDMenuGroup : NSObject

/*!
 @return NSString that appears at the top of the group.
 */
@property (nonatomic, nullable, copy) NSString* title;

/*!
 Creates a new WRLDMenuGroup with the specified title.
 @param title An NSString that appears at the top of the group.  If the title is nil the group will not display a title.
 */
- (instancetype) initWithTitle:(nullable NSString *)title;

/*!
 Add a menu option to the bottom of the group.
 @param option WRLDMenuOption to add.
 */
- (void) addOption: (WRLDMenuOption *)option;

/*!
 Creates a new option at the bottom of the group.  The created option can have an optional context that will be used when the option is selected but cannot have any submenu items within it.
 @param text NSString to be displayed representing the option.
 @param context NSObject to be passed to events when the option is selected.  Can be nil if there is no additional context.
 */
- (void) addOption: (NSString *)text
           context: (nullable NSObject *)context;

/*!
 Remove an option from the group.
 @param option WRLDMenuOption to be removed.
 */
- (void) removeOption: (WRLDMenuOption *)option;

/*!
 Insert an option into the group at the specified index.
 @param option WRLDMenuOption to be inserted.
 @param index NSUInteger index of the option.  The group title is not counted in the index.
 */
- (void) insertOption: (WRLDMenuOption *)option
             atIndex: (NSUInteger)index;

/*!
 Remove the menu option at the specified index from the group.
 @param index  NSUInteger index of the option to remove.  The group title is not counted in the index.
 */
- (void) removeOptionAtIndex: (NSUInteger)index;

/*!
 Removes all options from the group and leaves it empty.
 */
- (void) removeAllOptions;

@end

NS_ASSUME_NONNULL_END
