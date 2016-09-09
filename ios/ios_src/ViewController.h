// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#include "AppRunner.h"
#include "ViewWrap.h"

@interface ViewController : GLKViewController <UIGestureRecognizerDelegate>
{
    CFTimeInterval m_previousTimestamp;
    AppRunner* m_pAppRunner;
}

class ViewControllerWrapper : public ViewWrap<ViewController>
{
    using ViewWrap::ViewWrap;
};

@property (nonatomic, retain) UIView* pBackingView;

@end
