#pragma once

#include <Foundation/Foundation.h>

@protocol WRLDSearchResultModel;
@class WRLDSearchResultSelectedObserver;

typedef void (^ResultSelectedEvent) (id<WRLDSearchResultModel> selectedResultModel);

@interface WRLDSearchResultSelectedObserver : NSObject

- (void) addResultSelectedEvent :(ResultSelectedEvent) event;
- (void) removeResultSelectedEvent :(ResultSelectedEvent) event;

@end


