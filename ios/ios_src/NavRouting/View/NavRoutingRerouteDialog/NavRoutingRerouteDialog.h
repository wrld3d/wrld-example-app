#pragma once

#import <UIKit/UIKit.h>

#include "ICallback.h"

@interface NavRoutingRerouteDialog : UIView

@property(nonatomic, copy) IBOutlet NSString* message;

- (void) InsertRerouteDialogClosedCallback:(Eegeo::Helpers::ICallback1<const bool>*) rerouteDialogClosedCallback;
- (void) RemoveRerouteDialogClosedCallback:(Eegeo::Helpers::ICallback1<const bool>*) rerouteDialogClosedCallback;
@end
