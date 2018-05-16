#pragma once

#include "WRLDSearchProviderHandle.h"

@protocol WRLDSearchProvider;

@interface WRLDSearchProviderHandle (Private)

-(instancetype) initWithId: (NSInteger) uniqueId forProvider: (id<WRLDSearchProvider>) searchProvider;

@end

