// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

#include "ICallback.h"

@interface SurveyAlertViewHandler : NSObject<UIAlertViewDelegate>
{
    
}

- (id)initWithCallbacks:(Eegeo::Helpers::ICallback0&)acceptCallback
                         :(Eegeo::Helpers::ICallback0&)rejectCallback;

- (void)showAlert;

@end
