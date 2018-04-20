#pragma once
#import <Foundation/Foundation.h>

#import "WRLDSearchTypes.h"

@protocol WRLDSearchResultModel;
@protocol WRLDQueryFulfillerHandle;

@interface WRLDSearchQuery : NSObject

typedef NS_ENUM(NSInteger, ProgressStatus) {
    NotStarted,
    InFlight,
    Cancelled,
    Completed
};

@property (copy, readonly) NSString* queryString;
@property (readonly) ProgressStatus progress;
@property (readonly) BOOL hasSucceeded;
@property (readonly) BOOL hasCompleted;
@property (readonly) id<NSObject> queryContext;

- (WRLDSearchResultsCollection *) getResultsForFulfiller: (NSInteger) fulfillerHandleId;
- (void) cancel;
@end
