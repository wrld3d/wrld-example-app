#pragma once

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WRLDMenuChild : NSObject

@property (nonatomic, copy, readonly) NSString* text;

@property (nonatomic, copy, readonly) NSString* _Nullable icon;

@property (nonatomic, copy, readonly) NSObject* _Nullable context;

- (instancetype)initWithText:(NSString *)text
                        icon:(nullable NSString *)icon
                     context:(nullable NSObject *)context;

@end

NS_ASSUME_NONNULL_END
