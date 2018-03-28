#pragma once

#import <Foundation/Foundation.h>

@class WRLDMenuChild;

NS_ASSUME_NONNULL_BEGIN

@interface WRLDMenuOption : NSObject

@property (nonatomic, copy, readonly) NSString* text;

@property (nonatomic, copy, readonly) NSObject* _Nullable context;

- (instancetype)initWithText:(NSString *)text
                     context:(nullable NSObject *)context;

- (void)addChild:(WRLDMenuChild *)child;

- (void)addChild:(NSString *)text
            icon:(nullable NSString *)icon
         context:(nullable NSObject *)context;

- (void)removeChild:(WRLDMenuChild *)option;

- (void)insertChild:(WRLDMenuChild *)option
            atIndex:(NSUInteger)index;

- (void)removeChildAtIndex:(NSUInteger)index;

- (void)removeAllChildren;

@end

NS_ASSUME_NONNULL_END

