#pragma once

#import "SearchProvider.h"
#import <Foundation/Foundation.h>
#import <WRLDSearchWidget/WRLDSearchWidget.h>


@interface WidgetSearchProvider: NSObject <WRLDSearchProvider, WRLDSuggestionProvider>

- (instancetype) initWithSearchProvider: (ExampleApp::SearchProviders::SearchProvider*) searchProvider;
- (void) cancelAutocompleteRequest;

@end
