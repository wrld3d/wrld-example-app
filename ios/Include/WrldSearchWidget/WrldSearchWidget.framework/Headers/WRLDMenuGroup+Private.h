#pragma once

#include "WRLDMenuGroup.h"

@protocol WRLDMenuChangedListener;

@interface WRLDMenuGroup (Private)

- (NSMutableArray *)getOptions;

- (bool)hasTitle;

- (void)setListener:(id<WRLDMenuChangedListener>)listener;

@end

