#pragma once

#import <UIKit/UIKit.h>

@interface WRLDSearchWidgetTableViewContainer : UIView

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *flexibleHeightConstraint;


@property (weak, nonatomic) IBOutlet UIView *tableTopFade;
@property (weak, nonatomic) IBOutlet UIView *tableBottomFade;

- (void) initView;
- (void) createGradient;
- (void) setSeparatorColor: (UIColor *) color;
- (void) setDelegate: (id<UITableViewDelegate>) delegate;
- (void) setDataSource: (id<UITableViewDataSource>) dataSource;

- (void) registerNib: (UINib *) nib forCellReuseIdentifier: (NSString *) cellIdentifier;
- (void) reloadData;

- (void) updateScrollGradient: (BOOL) animate;
- (void) goToTop :(BOOL) animated;

- (void) setTableHeight: (CGFloat) height;
- (void) setUserInteractionEnabled: (BOOL) isUserInteractionEnabled;

@end

