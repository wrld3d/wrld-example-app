#pragma once

#import <UIKit/UIKit.h>
#import "WRLDSearchRequestFulfillerHandle.h"

@protocol WRLDSuggestionProvider;

@interface WRLDSuggestionProviderHandle : NSObject<WRLDSearchRequestFulfillerHandle>
@property (readonly) id<WRLDSuggestionProvider>  provider;
@end
