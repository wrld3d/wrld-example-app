#pragma once
#import <Foundation/Foundation.h>

#import "WRLDSearchTypes.h"

@protocol WRLDSearchResultsCollection;
@class WRLDSearchQuery;

@interface WRLDSearchRequest : NSObject

@property (copy, readonly) NSString* queryString;
@property (copy, readonly) id<NSObject> queryContext;
@property (readonly) BOOL hasCompleted;
-(void) cancel;
-(void) didComplete:(BOOL) success withResults:(WRLDSearchResultsCollection *) results;
@end

