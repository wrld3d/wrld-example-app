#pragma once

#import <Foundation/Foundation.h>
#import <WRLDSearchWidget/WRLDSearchQuery.h>

@interface WidgetQueryContext : NSObject
@property (nonatomic) BOOL clearPreviousResults;
@property (nonatomic) BOOL isTag;
@property (nonatomic) BOOL shouldTryInterior;
@property (nonatomic) BOOL usesLocation;
@property (nonatomic) BOOL usesRadius;

@property (nonatomic, strong) NSString* tagText;

@property (nonatomic) CGFloat latitude;
@property (nonatomic) CGFloat longtitude;
@property (nonatomic) CGFloat altitude;
@property (nonatomic) CGFloat radius;
@end
