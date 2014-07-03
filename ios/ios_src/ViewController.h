// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#include "AppRunner.h"

@interface ViewController : GLKViewController <UIGestureRecognizerDelegate>
{
	CFTimeInterval m_previousTimestamp;
    AppRunner* m_pAppRunner;
}

@end
