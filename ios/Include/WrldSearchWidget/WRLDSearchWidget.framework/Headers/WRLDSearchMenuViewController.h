#pragma once

#import <UIKit/UIKit.h>
#import "WRLDMenuChangedListener.h"

@class WRLDMenuObserver;
@class WRLDSearchMenuModel;
@class WRLDSearchWidgetStyle;
@class WRLDSearchMenuView;

NS_ASSUME_NONNULL_BEGIN

@interface WRLDSearchMenuViewController : NSObject <WRLDMenuChangedListener, UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, readonly) WRLDMenuObserver* observer;

- (instancetype) initWithView:(WRLDSearchMenuView *)view
                        style:(WRLDSearchWidgetStyle *)style;

- (void) setModel: (WRLDSearchMenuModel *) menuModel;
- (void) removeModel;

- (void)open;
- (void)close;
- (void)collapse;
- (void)expandAt:(NSUInteger)index;

- (void)onMenuButtonClicked;
- (void)onMenuBackButtonClicked;

- (BOOL)isMenuOpen;

@end

NS_ASSUME_NONNULL_END
