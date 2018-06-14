#pragma once

#include "WRLDMenuObserver.h"

@interface WRLDMenuObserver (Private)

- (void)opened:(BOOL)fromInteraction;

- (void)closed:(BOOL)fromInteraction;

- (void)selected:(NSObject *)optionContext;

- (void)expanded:(NSObject *)optionContext
 fromInteraction:(BOOL)fromInteraction;

- (void)collapsed:(NSObject *)optionContext
  fromInteraction:(BOOL)fromInteraction;

@end
