#pragma once

#include "WRLDSearchRequest.h"

@protocol WRLDSearchRequestFulfillerHandle;
@class WRLDSearchQuery;

@interface WRLDSearchRequest (Private)
-(instancetype) initWithFulfillerHandle: (id<WRLDSearchRequestFulfillerHandle>) fulfillerHandle forQuery:(WRLDSearchQuery *) query;
@end
