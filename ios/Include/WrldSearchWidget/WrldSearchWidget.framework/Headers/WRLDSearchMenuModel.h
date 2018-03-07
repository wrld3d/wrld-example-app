#pragma once

#import <UIKit/UIKit.h>

@protocol WRLDMenuChangedListener;
@class WRLDMenuGroup;

NS_ASSUME_NONNULL_BEGIN

@interface WRLDSearchMenuModel : NSObject

@property (nonatomic, copy) NSString* title;

- (void)setListener:(id<WRLDMenuChangedListener>)listener;

- (NSMutableArray *)getGroups;

- (void)addMenuGroup:(WRLDMenuGroup *)group;

- (void)removeMenuGroup:(WRLDMenuGroup *)group;

@end

NS_ASSUME_NONNULL_END
