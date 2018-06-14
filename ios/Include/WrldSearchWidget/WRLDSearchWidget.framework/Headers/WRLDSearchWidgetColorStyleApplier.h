#pragma once

#include <Foundation/Foundation.h>
#include "WRLDSearchWidgetStyle.h"

typedef NSMutableArray<ApplyColorEvent> ColorUpdateEventCollection;

@interface WRLDSearchWidgetColorStyleApplier : NSObject
- (void) apply;
@property (nonatomic, readonly) UIColor * color;
- (void) setColor: (UIColor *) color;
- (void) setColorFromInt: (NSInteger) colorHex;
- (void) addApplication: (ApplyColorEvent) event;
@end

