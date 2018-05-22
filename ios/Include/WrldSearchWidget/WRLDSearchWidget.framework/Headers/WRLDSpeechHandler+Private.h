
#pragma once

#include "WRLDSpeechCapture.h"
#include "WRLDSpeechObserver+Private.h"

@interface WRLDSpeechCapture (Private)
- (IBAction)outsideBoundsClickHandler:(id)sender;
- (IBAction)insideBoundsClickHandler:(id)sender;
- (IBAction)cancelButtonClickHandler:(id)sender;

-(void) show;
-(void) hide;
-(void) setInputVolume: (CGFloat) volume;

@end
