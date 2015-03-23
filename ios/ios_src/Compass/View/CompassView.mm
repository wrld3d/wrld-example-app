// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "CompassViewInterop.h"

@implementation CompassView

- (id) initWithParams:(float)width :(float)height :(float)pixelScale
{
    if(self = [super init])
    {
        m_pInterop = Eegeo_NEW(ExampleApp::Compass::View::CompassViewInterop)(self);
        m_stateChangeAnimationTimeSeconds = 0.2f;
        m_pixelScale = 1.f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        m_gpsIndicatorColour = ExampleApp::Helpers::ColorPalette::WhiteTone;

        //control positioning
        m_width = 80.f;
        m_height = 80.f;
        
        m_yPosBase = m_yPosActive = m_screenHeight - (8 * m_pixelScale) - m_height;
        m_yPosInactive = m_screenHeight + m_height;
        
        self.frame = CGRectMake(((m_screenWidth * 0.5f) - (m_width * 0.5f)), m_yPosInactive, m_width, m_height);

        //outer shape
        self.pOuterShape = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, m_width, m_height)] autorelease];
        self.pOuterShape.backgroundColor = [UIColor colorWithPatternImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"compass")];
        [self addSubview: self.pOuterShape];

        //inner shape
        const float innerWidth = 14.f;
        const float innerHeight = 14.f;
        self.pInnerShape = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, innerWidth, innerHeight)] autorelease];
        CAShapeLayer *circleLayer = [CAShapeLayer layer];
        [circleLayer setBounds:CGRectMake(0.0f, 0.0f, self.pInnerShape.bounds.size.width, self.pInnerShape.bounds.size.height)];
        [circleLayer setPosition:self.pOuterShape.center];
        UIBezierPath *path = [UIBezierPath bezierPathWithOvalInRect: CGRectMake(0.0f, 0.0f, innerWidth, innerHeight)];
        [circleLayer setPath:[path CGPath]];
        [circleLayer setStrokeColor:[[UIColor clearColor] CGColor]];
        [circleLayer setFillColor:[[UIColor clearColor] CGColor]];
        [circleLayer setLineWidth:1.0f];
        [[self.pInnerShape layer] addSublayer:circleLayer];
        [self addSubview: self.pInnerShape];
        
        //compass point
        float pointWidth = 7.f;
        float pointHeight = 26.f;
        self.pPoint = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, pointWidth, pointHeight)] autorelease];
        self.pPoint.backgroundColor = [UIColor colorWithPatternImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"CompassPoint")];
        self.pPoint.center = self.pOuterShape.center;
        [self addSubview: self.pPoint];

        m_tapGestureRecogniser = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_tapTabGesture:)] autorelease];
        [m_tapGestureRecogniser setDelegate:self];
        [self addGestureRecognizer: m_tapGestureRecogniser];
    }

    return self;
}

- (void)dealloc
{
    Eegeo_DELETE m_pInterop;
    [m_tapGestureRecogniser release];

    [self.pOuterShape removeFromSuperview];
    [self.pOuterShape release];

    [self.pInnerShape removeFromSuperview];
    [self.pInnerShape release];

    [self.pPoint removeFromSuperview];
    [self.pPoint release];

    [super dealloc];
}

- (void)layoutSubviews
{

}

- (void) showGpsDisabledView
{
    for (CAShapeLayer *layer in self.pInnerShape.layer.sublayers)
    {
        [layer setStrokeColor:[[UIColor clearColor] CGColor]];
        [layer setFillColor:[[UIColor clearColor] CGColor]];
    }
}

- (void) showGpsFollowView
{
    for (CAShapeLayer *layer in self.pInnerShape.layer.sublayers)
    {
        [layer setStrokeColor:[m_gpsIndicatorColour CGColor]];
        [layer setFillColor:[[UIColor clearColor] CGColor]];
    }
}

- (void) showGpsCompassModeView
{
    for (CAShapeLayer *layer in self.pInnerShape.layer.sublayers)
    {
        [layer setStrokeColor:[m_gpsIndicatorColour CGColor]];
        [layer setFillColor:[m_gpsIndicatorColour CGColor]];
    }
}

- (void) notifyGpsUnauthorized
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Location Services disabled"
                                                    message:@"GPS Compass inaccessable: Location Services are not enabled for this application. You can change this in your device settings."
                                                   delegate:nil
                                          cancelButtonTitle:@"OK"
                                          otherButtonTitles:nil];
    [alert show];
    [alert release];
}

- (void) updateHeading:(float)angleRadians
{
    self.pPoint.transform = CGAffineTransformTranslate(CGAffineTransformRotate(CGAffineTransformIdentity,
                                                                               -angleRadians),
                                                       0, -24.f);
}

- (ExampleApp::Compass::View::CompassViewInterop *)getInterop
{
    return m_pInterop;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return CGRectContainsPoint(self.bounds, touchLocation);
}

- (void) setFullyOnScreen
{
    if(self.frame.origin.y == m_yPosActive)
    {
        return;
    }
    
    [self animateToY:m_yPosActive];
}

- (void) setFullyOffScreen
{
    if(self.frame.origin.y == m_yPosInactive)
    {
        return;
    }
    
    [self animateToY:m_yPosInactive];
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    float newY = m_yPosInactive + (m_yPosActive - m_yPosInactive) * onScreenState;
    
    self.hidden = false;
    CGRect f = self.frame;
    f.origin.y = newY;
    self.frame = f;
}

- (void) animateToY:(float)y
{
    CGRect f = self.frame;
    f.origin.y = y;
    
    if(y != m_yPosInactive)
    {
        self.hidden = false;
    }
    
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds animations:^
     {
         self.frame = f;
     } completion:^(BOOL finished)
     {
         self.hidden = (y == m_yPosInactive);
     }
     ];
}

- (void)_tapTabGesture:(UITapGestureRecognizer *)recognizer
{
    m_pInterop->OnCycle();
}

@end

