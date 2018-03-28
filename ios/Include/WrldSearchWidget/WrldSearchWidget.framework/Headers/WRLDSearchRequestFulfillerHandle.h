#pragma once

#import <UIKit/UIKit.h>

@protocol WRLDSearchResultModel;
@class WRLDSearchResultSelectedObserver;

@protocol WRLDSearchRequestFulfillerHandle
@property (readonly) NSInteger identifier;
@property (nonatomic, readonly) CGFloat cellHeight;
@property (nonatomic, readonly) NSString* cellIdentifier;
@property (nonatomic, readonly) NSString* moreResultsName;
@property (nonatomic, readonly) WRLDSearchResultSelectedObserver* selectionObserver;
@end

