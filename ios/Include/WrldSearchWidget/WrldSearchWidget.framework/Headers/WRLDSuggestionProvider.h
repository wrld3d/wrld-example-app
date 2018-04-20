#pragma once

#import <Foundation/Foundation.h>

@class WRLDSearchRequest;

@class WRLDSearchQuery;
@protocol WRLDSuggestionProvider
- (void) getSuggestions: (WRLDSearchRequest *) query;
@end
