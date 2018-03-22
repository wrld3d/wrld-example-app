#pragma once

#import <Foundation/Foundation.h>

@class WRLDMenuOption;

NS_ASSUME_NONNULL_BEGIN

@interface WRLDMenuGroup : NSObject

@property (nonatomic, nullable, copy) NSString* title;

- (instancetype)initWithTitle:(nullable NSString *)title;

- (void)addOption:(WRLDMenuOption *)option;

- (void)addOption:(NSString *)text
          context:(nullable NSObject *)context;

- (void)removeOption:(WRLDMenuOption *)option;

- (void)insertOption:(WRLDMenuOption *)option
             atIndex:(NSUInteger)index;

- (void)removeOptionAtIndex:(NSUInteger)index;

- (void)removeAllOptions;

@end

NS_ASSUME_NONNULL_END
