#pragma once

#import <Foundation/Foundation.h>

@class WRLDMenuChild;

NS_ASSUME_NONNULL_BEGIN

@interface WRLDMenuOption : NSObject

@property (nonatomic, copy) NSString* text;

@property (nonatomic, copy) NSObject* _Nullable context;

- (instancetype)initWithText:(NSString *)text
                     context:(nullable NSObject *)context;

- (bool)hasChildren;

- (NSMutableArray *)getChildren;

- (void)addChild:(WRLDMenuChild *)child;

- (void)addChild:(NSString *)text
            icon:(nullable NSString *)icon
         context:(nullable NSObject *)context;

@end

NS_ASSUME_NONNULL_END

