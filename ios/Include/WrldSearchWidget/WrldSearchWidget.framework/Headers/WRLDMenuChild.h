#pragma once

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WRLDMenuChild : NSObject

@property (nonatomic, copy) NSString* text;

@property (nonatomic, copy) NSString* _Nullable icon;

@property (nonatomic, copy) NSObject* _Nullable context;

- (instancetype)initWithText:(NSString *)text
                        icon:(nullable NSString *)icon
                     context:(nullable NSObject *)context;

@end

NS_ASSUME_NONNULL_END
