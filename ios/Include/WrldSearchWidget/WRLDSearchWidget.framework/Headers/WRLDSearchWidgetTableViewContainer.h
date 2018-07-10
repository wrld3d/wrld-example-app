#pragma once

#import <UIKit/UIKit.h>

@class WRLDFadeableTableView;

@interface WRLDSearchWidgetTableViewContainer : UIView

@property (weak, nonatomic) IBOutlet WRLDFadeableTableView *tableView;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *flexibleHeightConstraint;

- (void) initView;
- (void) setSeparatorColor: (UIColor *) color;
- (void) setDelegate: (id<UITableViewDelegate>) delegate;
- (void) setDataSource: (id<UITableViewDataSource>) dataSource;

- (void) registerNib: (UINib *) nib forCellReuseIdentifier: (NSString *) cellIdentifier;
- (void) reloadData;

- (void) goToTop :(BOOL) animated;

- (void) setTableHeight: (CGFloat) height;
- (void) setUserInteractionEnabled: (BOOL) isUserInteractionEnabled;

@end

