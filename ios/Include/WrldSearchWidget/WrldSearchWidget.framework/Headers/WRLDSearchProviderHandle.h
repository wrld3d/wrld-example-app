#pragma once

#import <UIKit/UIKit.h>
#import "WRLDSearchRequestFulfillerHandle.h"

@protocol WRLDSearchProvider;

/*!
 A reference to a WRLDSearchProvider that has been added to a WRLDSearchModel.
 Used to add the provider to WRLDSearchWidgetView, to remove it from the WRLDSearchModel.
 and to get provider specific results from a WRLDSearchQuery.
 */
@interface WRLDSearchProviderHandle : NSObject<WRLDSearchRequestFulfillerHandle>

/*!
 A reference to the WRLDSearchProvider the handle corresponds to.
 */
@property (readonly) id<WRLDSearchProvider> provider;
@end
