#pragma once

#import <UIKit/UIKit.h>

@class WRLDSearchRequest;

@protocol WRLDSearchProvider
@property (nonatomic, readonly, copy) NSString *moreResultsName;
@property (nonatomic, readonly, copy) NSString *cellIdentifier;
@property (nonatomic, readonly) CGFloat cellHeight;
- (void) searchFor: (WRLDSearchRequest *) query;

@end
