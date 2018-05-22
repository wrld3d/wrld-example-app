#pragma once

#import <UIKit/UIKit.h>

@protocol WRLDMenuChangedListener;
@class WRLDMenuGroup;

NS_ASSUME_NONNULL_BEGIN

/*!
 Models the search menu.
 */
@interface WRLDSearchMenuModel : NSObject

/*!
 NSString title displayed at the top of the menu.
 */
@property (nonatomic, copy) NSString* title;

/*!
 Add a new group to the bottom of the menu.
 @param group WRLDMenuGroup to add.
 */
- (void) addMenuGroup: (WRLDMenuGroup *) group;

/*!
 Remove a group from the menu.
 @param group WRLDMenuGroup to remove.
 */
- (void) removeMenuGroup: (WRLDMenuGroup *) group;

/*!
 Insert a group into the menu.
 @param group WRLDMenuGroup to add.
 @param index NSUInteger position within the menu to insert the group.
 */
- (void) insertMenuGroup: (WRLDMenuGroup *) group
                 atIndex: (NSUInteger) index;

/*!
 Remove a group from the menu.
 @param index Position within the menu of the group to remove.
 */
- (void) removeMenuGroupAtIndex: (NSUInteger) index;

/*!
 Remove all groups from the search menu.
 */
- (void) removeAllGroups;

@end

NS_ASSUME_NONNULL_END
