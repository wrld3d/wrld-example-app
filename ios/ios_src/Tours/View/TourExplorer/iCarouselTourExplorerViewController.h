// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "Tours.h"
#include "TourExplorerViewInterop.h"

@class ImageStore;

@interface iCarouselTourExplorerViewController : NSObject

-(id) initWithParams:(float)width
                    :(float)height
                    :(float)pixelScale
                    :(id)interactionHandlerInstance
                    :(SEL)selectionInteractionHandler
                    :(SEL)selectionTappedHandler
                    :(SEL)currentItemChangedHandler
                    :(ExampleApp::Tours::View::TourExplorer::TourExplorerViewInterop*)pInterop
                    :(ImageStore*)pImageStore;

- (void) configureTourStatesPresentation:(const ExampleApp::Tours::SdkModel::TourModel&)tour;

-(UIView*) getView;

-(void) resetView:(int)initialCard;

-(int) getItemCount;

-(int) getSelectionIndex;

-(float) getItemWidth;

-(float) getItemHeight;

@end
