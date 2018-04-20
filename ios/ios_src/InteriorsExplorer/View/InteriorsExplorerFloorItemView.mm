// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerFloorItemView.h"

@implementation InteriorsExplorerFloorItemView


- (id) initWithFrame:(CGRect)frame
             spacing:(CGFloat)labelSpacing
        dividerWidth:(CGFloat)dividerWidth
             centerX:(CGFloat)centerlineX
     reuseIdentifier:(NSString*)reuseId;
{
    if (self = [super initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reuseId])
    {
        self.frame = frame;
        CGFloat height = frame.size.height;
        
        self.backgroundColor=[UIColor clearColor];
        
        UIBezierPath* linePath = [UIBezierPath bezierPath];
        UIBezierPath* topPath = [UIBezierPath bezierPath];
        UIBezierPath* bottomPath = [UIBezierPath bezierPath];
        
        // Horizontal centerline.
        [linePath moveToPoint:CGPointMake(centerlineX - 0.5*dividerWidth, height*0.5f)];
        [linePath addLineToPoint:CGPointMake(centerlineX + 0.5*dividerWidth, height*0.5f)];
        
        [topPath moveToPoint:CGPointMake(centerlineX, 0.0f)];
        [topPath addLineToPoint:CGPointMake(centerlineX, height*0.5f)];
        
        [bottomPath moveToPoint:CGPointMake(centerlineX, height*0.5f)];
        [bottomPath addLineToPoint:CGPointMake(centerlineX, height)];

        self.pDivisionShape = [CAShapeLayer layer];
        self.pDivisionShape.path = [linePath CGPath];
        self.pDivisionShape.strokeColor = [[UIColor whiteColor] CGColor];
        self.pDivisionShape.lineWidth = 1.0f;
        
        self.pTopDivisionShape = [CAShapeLayer layer];
        self.pTopDivisionShape.path = [topPath CGPath];
        self.pTopDivisionShape.strokeColor = [[UIColor whiteColor] CGColor];
        self.pTopDivisionShape.lineWidth = 1.0f;
        
        self.pBottomDivisionShape = [CAShapeLayer layer];
        self.pBottomDivisionShape.path = [bottomPath CGPath];
        self.pBottomDivisionShape.strokeColor = [[UIColor whiteColor] CGColor];
        self.pBottomDivisionShape.lineWidth = 1.0f;
        
        [self.layer addSublayer:self.pDivisionShape];
        CGFloat labelWidth = centerlineX - labelSpacing - 0.5*dividerWidth;
        self.pFloorNameLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0.0f, 0.0f, labelWidth, height)] autorelease];
        self.pFloorNameLabel.lineBreakMode = NSLineBreakByClipping;
        self.pFloorNameLabel.adjustsFontSizeToFitWidth = NO;
        self.pFloorNameLabel.textColor = [UIColor whiteColor];
        self.pFloorNameLabel.textAlignment = NSTextAlignmentRight;
     
        [self addSubview:self.pFloorNameLabel];
        
        self.userInteractionEnabled = false;
        self.pFloorNameLabel.userInteractionEnabled = false;
        
    }
    return self;
}

- (void)setFloor :(NSString*)floorName :(BOOL)isTop :(BOOL)isBottom
{
    self.pFloorNameLabel.text = floorName;
  
    [self.pTopDivisionShape removeFromSuperlayer];
    [self.pBottomDivisionShape removeFromSuperlayer];
    
    if(!isTop)
    {
        [self.layer addSublayer:self.pTopDivisionShape];
    }
    if(!isBottom)
    {
        [self.layer addSublayer:self.pBottomDivisionShape];
    }
}

- (void)dealloc
{
    [self.pFloorNameLabel removeFromSuperview];
    self.pFloorNameLabel = nil;
    
    [self removeFromSuperview];
    [super dealloc];
}

@end
