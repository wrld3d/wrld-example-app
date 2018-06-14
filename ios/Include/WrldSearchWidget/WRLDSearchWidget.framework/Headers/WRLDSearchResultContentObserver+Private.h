
#pragma once

#include "WRLDSearchResultContentObserver.h"

@interface WRLDSearchResultContentObserver(Private)

-(void) willPopulate: (WRLDSearchResultTableViewCell*) cell;
-(void) didPopulate: (WRLDSearchResultTableViewCell*) cell withContent: (id<WRLDSearchResultModel>) model;

@end
