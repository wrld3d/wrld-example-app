#pragma once

#import <UIKit/UIKit.h>
#include "WrldSearchWidget/WrldSearchWidget.h"

@interface NavSearchContainerView : UIView
- (instancetype) initWithSubviews: (WRLDSearchWidgetView*) searchView :(UIView*) resultsView :(UIView*) backButton :(UIView*) searchHintContainer;
@end
