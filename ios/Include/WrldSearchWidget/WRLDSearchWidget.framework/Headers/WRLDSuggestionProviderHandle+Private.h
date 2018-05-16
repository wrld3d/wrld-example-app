#pragma once

#include "WRLDSuggestionProviderHandle.h"

@protocol WRLDSuggestionProvider;

@interface WRLDSuggestionProviderHandle (Private)

- (instancetype) initWithId: (NSInteger) uniqueId forProvider: (id<WRLDSuggestionProvider>) suggestionProvider;

@end
