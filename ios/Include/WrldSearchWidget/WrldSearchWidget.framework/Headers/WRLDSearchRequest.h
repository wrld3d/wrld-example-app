#pragma once
#import <Foundation/Foundation.h>

#import "WRLDSearchTypes.h"

@protocol WRLDSearchResultsCollection;

@interface WRLDSearchRequest : NSObject

@property (copy, readonly) NSString* queryString;
@property (readonly) BOOL hasCompleted;
-(void) cancel;
-(void) didComplete:(BOOL) success withResults:(WRLDSearchResultsCollection *) results;
@end

