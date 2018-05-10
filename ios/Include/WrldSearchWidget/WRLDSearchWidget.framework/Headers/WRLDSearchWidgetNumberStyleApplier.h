#pragma once

#include <Foundation/Foundation.h>
#include "WRLDSearchWidgetStyle.h"

typedef NSMutableArray<ApplyNumberEvent> NumberUpdateEventCollection;

@interface WRLDSearchWidgetNumberStyleApplier : NSObject
- (void) apply;
@property (nonatomic, readonly) CGFloat number;
- (void) setNumber: (CGFloat) number;
- (void) addApplication: (ApplyNumberEvent) event;
@end

