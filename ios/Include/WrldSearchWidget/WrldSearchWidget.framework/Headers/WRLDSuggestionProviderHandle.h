#pragma once

#import <UIKit/UIKit.h>
#import "WRLDSearchRequestFulfillerHandle.h"

@protocol WRLDSuggestionProvider;

/*!
 A reference to a WRLDSuggestionProvider that has been added to a WRLDSearchModel.
 Used to add the provider to WRLDSearchWidgetView, to remove it from the WRLDSearchModel.
 and to get provider specific results from a WRLDSearchQuery.
 */
@interface WRLDSuggestionProviderHandle : NSObject<WRLDSearchRequestFulfillerHandle>

/*!
 A reference to the WRLDSuggestionProvider the handle corresponds to.
 */
@property (readonly) id<WRLDSuggestionProvider>  provider;
@end
