// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#include "AppRunner.h"

@interface ViewController : GLKViewController <UIGestureRecognizerDelegate>
{
    CFTimeInterval m_previousTimestamp;
    AppRunner* m_pAppRunner;
}

@property (nonatomic, retain) UIView* pBackingView;

@end
