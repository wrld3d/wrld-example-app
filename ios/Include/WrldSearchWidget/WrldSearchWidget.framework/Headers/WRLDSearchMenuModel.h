#pragma once

#import <UIKit/UIKit.h>

@protocol WRLDMenuChangedListener;
@class WRLDMenuGroup;

NS_ASSUME_NONNULL_BEGIN

@interface WRLDSearchMenuModel : NSObject

@property (nonatomic, copy) NSString* title;

- (void)addMenuGroup:(WRLDMenuGroup *)group;

- (void)removeMenuGroup:(WRLDMenuGroup *)group;

- (void)insertMenuGroup:(WRLDMenuGroup *)group
                atIndex:(NSUInteger)index;

- (void)removeMenuGroupAtIndex:(NSUInteger)index;

- (void)removeAllGroups;

@end

NS_ASSUME_NONNULL_END
