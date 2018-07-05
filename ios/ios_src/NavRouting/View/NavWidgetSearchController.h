#pragma once

#import <UIKit/UIKit.h>
#include "WrldNav/WrldNav.h"
#include "NavWidgetViewIncludes.h"

@interface NavWidgetSearchController : NSObject<WRLDNavModelEventListener>
- (instancetype) initWithSearchView: (ExampleApp::NavRouting::View::NavWidgetSearchView*) searchView navWidgetView : (ExampleApp::NavRouting::View::NavWidgetView*) navWidgetView;

- (void) handleLocationSet: (BOOL)wasStartLocation;
@end
