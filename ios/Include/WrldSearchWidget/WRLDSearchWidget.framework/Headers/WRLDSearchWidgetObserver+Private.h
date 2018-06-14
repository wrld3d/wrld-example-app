#pragma once

#include <Foundation/Foundation.h>
#include "WRLDSearchWidgetObserver.h"

@interface WRLDSearchWidgetObserver (Private)

- (void)searchbarGainFocus;

- (void)searchbarResignFocus;

- (void)searchbarTextChanged: (NSString *) newText;

- (void)searchWidgetGainFocus;

- (void)searchWidgetResignFocus;

- (void)receiveSearchResults;

- (void)clearSearchResults;

- (void)showSearchResults;

- (void)hideSearchResults;

@end

