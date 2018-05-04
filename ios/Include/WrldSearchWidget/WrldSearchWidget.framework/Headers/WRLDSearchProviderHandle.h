#pragma once

#import <UIKit/UIKit.h>
#import "WRLDSearchRequestFulfillerHandle.h"

@protocol WRLDSearchProvider;

@interface WRLDSearchProviderHandle : NSObject<WRLDSearchRequestFulfillerHandle>
@property (readonly) id<WRLDSearchProvider> provider;
@end
