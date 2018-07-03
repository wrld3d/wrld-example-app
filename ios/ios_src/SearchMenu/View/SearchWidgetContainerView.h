
#pragma once

#import <UIKit/UIKit.h>
#include "SearchWidgetView.h"
#import "WidgetSearchProvider.h"

@interface SearchWidgetContainerView : UIView

- (instancetype)initWithSearchModel: (WRLDSearchModel*) searchModel
                     searchProvider: (WidgetSearchProvider *) searchProvider
                  navigationEnabled: (BOOL) isNavigationEnabled
                         messageBus: (ExampleApp::ExampleAppMessaging::TMessageBus &) messageBus;

- (ExampleApp::SearchMenu::View::SearchWidgetView*) getInterop;
- (BOOL) consumesTouch:(UITouch *)touch;
@property (nonatomic, retain) UIView *widget;
@property (nonatomic, retain) UIView *speechWidget;

@end
