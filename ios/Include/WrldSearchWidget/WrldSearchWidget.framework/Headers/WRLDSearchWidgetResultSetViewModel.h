#pragma once

#import <UIKit/UIKit.h>
#import "WRLDSearchTypes.h"

@class WRLDSearchQuery;
@protocol WRLDSearchRequestFulfillerHandle;
@protocol WRLDSearchResultModel;

@interface WRLDSearchWidgetResultSetViewModel : NSObject

typedef NS_ENUM(NSInteger, WRLDSearchResultSetExpandedStateType) {
    WRLDSearchResultSetExpandedStateHidden,
    WRLDSearchResultSetExpandedStateCollapsed,
    WRLDSearchResultSetExpandedStateExpanded
};

@property (nonatomic, readonly) id<WRLDSearchRequestFulfillerHandle> fulfiller;
@property (nonatomic, readonly) WRLDSearchResultSetExpandedStateType expandedState;

- (instancetype) initForRequestFulfiller: (id<WRLDSearchRequestFulfillerHandle>) requestFulfillerHandle
                  maxToShowWhenCollapsed: (NSInteger) maxToShowWhenCollapsed
                   maxToShowWhenExpanded: (NSInteger) maxToShoWhenExpanded;

- (void) updateResultData: (WRLDSearchResultsCollection *) results;
- (void) setExpandedState: (WRLDSearchResultSetExpandedStateType) state;

- (void) setMaxResultsToShowWhenCollapsed: (NSInteger) maxToShowWhenCollapsed;
- (void) setMaxResultsToShowWhenExpanded: (NSInteger) maxToShoWhenExpanded;

- (CGFloat) getResultsCellHeightWhen: (WRLDSearchResultSetExpandedStateType) expandedState;
- (NSInteger) getVisibleResultCountWhen: (WRLDSearchResultSetExpandedStateType) expandedState;
- (BOOL) hasMoreResultsCellWhen: (WRLDSearchResultSetExpandedStateType) expandedState;

- (id<WRLDSearchResultModel>) getResult: (NSInteger) index;
- (NSInteger) getResultCount;
- (BOOL) isMoreResultsCell: (NSInteger) row;

@end



