// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerFloorItemView.h"

@implementation InteriorsExplorerFloorItemView

- (id) initWithParams:(float)width :(float)height :(float)pixelScale :(NSString*)floorName :(BOOL)isTop :(BOOL)isBottom
{
    if (self = [super init])
    {
        self.frame = CGRectMake(0, 0, width, height);
        
        UIBezierPath* path = [UIBezierPath bezierPath];
        
        // Horizontal centerline.
        [path moveToPoint:CGPointMake(0.0f, height*0.5f)];
        [path addLineToPoint:CGPointMake(width*0.5f, height*0.5f)];
        
        // Vertical centerline
        if(!isTop)
        {
            [path moveToPoint:CGPointMake(width*0.25f, 0.0f)];
            [path addLineToPoint:CGPointMake(width*0.25f, height*0.5f)];
        }
        if(!isBottom)
        {
            [path moveToPoint:CGPointMake(width*0.25f, height*0.5f)];
            [path addLineToPoint:CGPointMake(width*0.25f, height)];
        }
        
        CAShapeLayer* shapeLayer = [CAShapeLayer layer];
        shapeLayer.path = [path CGPath];
        shapeLayer.strokeColor = [[UIColor whiteColor] CGColor];
        shapeLayer.lineWidth = 1.0f;
        
        [self.layer addSublayer:shapeLayer];
        
        const float textSpacing = 5;
        self.pFloorNameLabel = [[[UILabel alloc] initWithFrame:CGRectMake(width*0.5f + textSpacing, 0.0f, width*0.5f, height)] autorelease];
        self.pFloorNameLabel.lineBreakMode = NSLineBreakByClipping;
        self.pFloorNameLabel.adjustsFontSizeToFitWidth = NO;
        self.pFloorNameLabel.textColor = [UIColor whiteColor];
        self.pFloorNameLabel.textAlignment = NSTextAlignmentLeft;
        self.pFloorNameLabel.text = floorName;
        [self addSubview:self.pFloorNameLabel];
        
        self.userInteractionEnabled = false;
        self.pFloorNameLabel.userInteractionEnabled = false;
        
        [self hideName];
        
        
    }
    return self;
}

- (void)dealloc
{
    [self.pFloorNameLabel removeFromSuperview];
    self.pFloorNameLabel = nil;
    
    [self removeFromSuperview];
    [super dealloc];
}

- (void) showName
{
    [self.layer removeAllAnimations];
    
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:0.25];
    [UIView setAnimationBeginsFromCurrentState:YES];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
    
    self.alpha = 1.0f;
    self.pFloorNameLabel.alpha = 1.0f;
    
    [UIView commitAnimations];
}

- (void) hideName
{
    [self.layer removeAllAnimations];
    
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:0.25];
    [UIView setAnimationBeginsFromCurrentState:YES];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
    
    self.alpha = 0.5f;
    self.pFloorNameLabel.alpha = 0.0f;
    
    [UIView commitAnimations];
}

@end