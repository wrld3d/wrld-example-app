#pragma once

#import "WRLDSearchMenuModel.h"

@protocol WRLDMenuChangedListener;

@interface WRLDSearchMenuModel (Private)

- (NSMutableArray *)getGroups;

- (void)setListener:(id<WRLDMenuChangedListener>)listener;

@end


