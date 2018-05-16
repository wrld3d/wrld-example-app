#pragma once

#include "WRLDMenuOption.h"

@protocol WRLDMenuChangedListener;

@interface WRLDMenuOption (Private)

- (bool)hasChildren;

- (NSMutableArray *)getChildren;

- (void)setListener:(id<WRLDMenuChangedListener>)listener;

@end


