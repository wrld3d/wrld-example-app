#pragma once

#import <WRLDSearchWidget/WRLDSearchWidget.h>
#include "ISearchNavigationHandler.h"

@interface WidgetSearchResultTableViewCell : WRLDSearchResultTableViewCell
- (void) setNavigationHidden:(BOOL) isNavigationHidden;
- (void) assignNavigationHandler: (ExampleApp::SearchMenu::ISearchNavigationHandler *) navigationHandler;
@end
