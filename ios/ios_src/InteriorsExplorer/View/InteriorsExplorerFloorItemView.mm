// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerFloorItemView.h"

@implementation InteriorsExplorerFloorItemView

- (id) initWithParams:(float)labelWidth :(float)labelSpacing :(float)divisionWidth :(float)height :(float)pixelScale :(NSString*)floorName :(BOOL)isTop :(BOOL)isBottom
{
    if (self = [super init])
    {
        self.frame = CGRectMake(0, 0, labelWidth+divisionWidth+labelSpacing, height);
        
        UIBezierPath* path = [UIBezierPath bezierPath];
        
        // Horizontal centerline.
        [path moveToPoint:CGPointMake(labelWidth+labelSpacing, height*0.5f)];
        [path addLineToPoint:CGPointMake(labelWidth+labelSpacing+divisionWidth, height*0.5f)];
        
        float centerlineX = labelWidth + labelSpacing + 0.5f * divisionWidth;
        // Vertical centerline
        if(!isTop)
        {
            [path moveToPoint:CGPointMake(centerlineX, 0.0f)];
            [path addLineToPoint:CGPointMake(centerlineX, height*0.5f)];
        }
        if(!isBottom)
        {
            [path moveToPoint:CGPointMake(centerlineX, height*0.5f)];
            [path addLineToPoint:CGPointMake(centerlineX, height)];
        }
        
        CAShapeLayer* shapeLayer = [CAShapeLayer layer];
        shapeLayer.path = [path CGPath];
        shapeLayer.strokeColor = [[UIColor whiteColor] CGColor];
        shapeLayer.lineWidth = 1.0f;
        
        [self.layer addSublayer:shapeLayer];
        
        self.pFloorNameLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0.0f, 0.0f, labelWidth, height)] autorelease];
        self.pFloorNameLabel.lineBreakMode = NSLineBreakByClipping;
        self.pFloorNameLabel.adjustsFontSizeToFitWidth = NO;
        self.pFloorNameLabel.textColor = [UIColor whiteColor];
        self.pFloorNameLabel.textAlignment = NSTextAlignmentRight;
        self.pFloorNameLabel.text = floorName;
        //[self.pFloorNameLabel sizeToFit];
        CGRect f = self.pFloorNameLabel.frame;
        f.size.height = height;
        self.pFloorNameLabel.frame = f;
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
