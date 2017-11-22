// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "InteriorsExplorerViewIncludes.h"
#include "InteriorStreamingDialogSpinner.h"

@class InteriorStreamingDialogView;

@interface InteriorStreamingDialogView : UIView
{
    ExampleApp::InteriorsExplorer::View::InteriorStreamingDialogViewInterop* m_pInterop;
    
    float m_width;
    float m_height;
    
    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale;

- (ExampleApp::InteriorsExplorer::View::InteriorStreamingDialogViewInterop*) getInterop;

- (void) show;

- (void) hide;

@property (nonatomic, retain) UIView* pControlContainer;
@property (nonatomic, retain) UIImageView* pStreamingCompleteImage;
@property (nonatomic, retain) InteriorStreamingDialogSpinner* pSpinner;
@property (nonatomic, retain) UILabel* pMainLabel;
@property (nonatomic, retain) UILabel* pDescriptionLabel;
@property (nonatomic, retain) UIView* pDescriptionLabelSeparator;

@end
