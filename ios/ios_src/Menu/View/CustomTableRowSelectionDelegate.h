// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>

@protocol CustomTableRowSelectionDelegate <NSObject>

- (void)onSectionExpanded;

- (void)onSectionContracted;

- (void)onRowSelected;

@end
