#pragma once

#include "WRLDSearchQueryObserver.h"

@interface WRLDSearchQueryObserver (Private)

- (void) didComplete : (WRLDSearchQuery *) query;
- (void) willSearchFor: (WRLDSearchQuery *) query;
- (void) cancelled: (WRLDSearchQuery *) query;

@end

