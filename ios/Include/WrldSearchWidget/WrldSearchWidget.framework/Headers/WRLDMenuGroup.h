#pragma once

#import <Foundation/Foundation.h>

@class WRLDMenuOption;

NS_ASSUME_NONNULL_BEGIN

@interface WRLDMenuGroup : NSObject

@property (nonatomic) NSString* _Nullable title;

- (instancetype)initWithTitle:(nullable NSString *)title;

- (void)addOption:(WRLDMenuOption *)option;

- (void)addOption:(NSString *)text
          context:(nullable NSObject *)context;

@end

NS_ASSUME_NONNULL_END
