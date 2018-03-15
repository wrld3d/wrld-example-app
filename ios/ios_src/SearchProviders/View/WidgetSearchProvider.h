#pragma once

#import "ISearchProvider.h"
#import <Foundation/Foundation.h>
#import <WRLDSearchWidget/WRLDSearchWidget.h>


@interface WidgetSearchProvider: NSObject <WRLDSearchProvider, WRLDSuggestionProvider>

- (instancetype) initWithSearchProvider: (ExampleApp::SearchMenu::View::ISearchProvider *) searchProvider;

@end
