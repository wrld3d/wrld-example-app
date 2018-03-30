//
//  SearchWidgetView.h
//  ProjectSwallowApp
//
//  Created by David Crooks on 28/03/2018.
//
#pragma once

#import <UIKit/UIKit.h>
#include "SearchWidgetView.h"
#import "WidgetSearchProvider.h"

@interface SearchWidgetContainerView : UIView

- (instancetype)initWithSearchProvider:(WidgetSearchProvider *) searchProvider
                            messageBus:(ExampleApp::ExampleAppMessaging::TMessageBus &) messageBus;
- (ExampleApp::SearchMenu::View::SearchWidgetView*) getInterop;
- (BOOL) consumesTouch:(UITouch *)touch;
@property (nonatomic, retain) UIView *widget;

@end
