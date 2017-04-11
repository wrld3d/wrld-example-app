// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "CompassViewInterop.h"

static const float CompassOuterShapeInactiveAlpha = 0.5f;
static const float CompassOuterShapeActiveAlpha = 1.0f;

static const float RotationHighlightAnimationSeconds = 0.2;

enum CompassViewState
{
    Disabled,
    Follow,
    Compass
};

@interface CompassView()
{
    UIImage* m_pCompassDefaultImage;
    UIImage* m_pCompassDefaultHighlightImage;
    UIImage* m_CompassRingImage;
    UIImage* m_pCompassLockedImage;
    UIImage* m_pCompassLockedHighlightedImage;
    UIImage* m_pCompassUnlockedImage;
    UIImage* m_pCompassUnlockedHighlightedImage;
    
    CompassViewState m_compassViewState;
    
    bool m_disabledStateHighlighted;
    float m_currentAngleRadians;
}

@end

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
        
        m_compassViewState = Disabled;
        
        //control positioning
        m_width = 80.f;
        m_height = 80.f;
        
        m_innerHeight = 80.0f/1.5f;
        m_innerWidth = 80.0f/1.5f;
        
        m_yPosBase = m_yPosActive = m_screenHeight - (8 * m_pixelScale) - m_innerHeight - (m_height - m_innerHeight)/2;
        m_yPosInactive = m_screenHeight + m_height;
        
        self.frame = CGRectMake(((m_screenWidth * 0.5f) - (m_innerWidth * 0.5f)), m_yPosInactive, m_width, m_height);
        
        self->m_pCompassDefaultImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"CompassNewLocate") retain];
        self->m_pCompassDefaultHighlightImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"CompassNewLocate_Down") retain];
        self->m_CompassRingImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"CompassNew") retain];
        self->m_pCompassLockedImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"CompassNewLocked") retain];
        self->m_pCompassLockedHighlightedImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"CompassNewLocked_Down") retain];
        self->m_pCompassUnlockedImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"CompassNewUnlocked") retain];
        self->m_pCompassUnlockedHighlightedImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"CompassNewUnlocked_Down") retain];
        
        //outer shape
        self.pOuterShape = [[[UIImageView alloc] initWithFrame:CGRectMake(0.f, 0.f, m_innerWidth, m_innerHeight)] autorelease];
        self.pOuterShape.image = m_pCompassDefaultImage;
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

        self.pPoint = [[[UIImageView alloc] initWithFrame:CGRectMake(0.f, 0.f, m_width, m_height)] autorelease];
        self.pPoint.image = m_CompassRingImage;
        self.pPoint.center = self.pOuterShape.center;
        [self addSubview: self.pPoint];
        
        self.hidden = YES;
        
        m_disabledStateHighlighted = false;

        m_currentAngleRadians = 0.0f;
        self.pPoint.alpha = CompassOuterShapeInactiveAlpha;
    }

    return self;
}

- (void)dealloc
{
    Eegeo_DELETE m_pInterop;

    [self.pOuterShape removeFromSuperview];
    [self.pOuterShape release];

    [self.pInnerShape removeFromSuperview];
    [self.pInnerShape release];

    [self.pPoint removeFromSuperview];
    [self.pPoint release];
    
    [self->m_pCompassDefaultImage release];
    [self->m_pCompassDefaultHighlightImage release];
    [self->m_CompassRingImage release];
    [self->m_pCompassLockedImage release];
    [self->m_pCompassLockedHighlightedImage release];
    [self->m_pCompassUnlockedImage release];
    [self->m_pCompassUnlockedHighlightedImage release];

    [super dealloc];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self setHighlighted:YES];
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint touchLocation = [touch locationInView:self];
    if(CGRectContainsPoint(self.bounds, touchLocation))
    {
        [self setHighlighted:YES];
    }
    else
    {
        [self setHighlighted:NO];
    }
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint touchLocation = [touch locationInView:self];
    
    [self setHighlighted:NO];
    if(CGRectContainsPoint(self.bounds, touchLocation))
    {
        m_pInterop->OnCycle();
    }
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self setHighlighted:NO];
}

- (void) showGpsDisabledView
{
    m_compassViewState = Disabled;
    
    if (!m_disabledStateHighlighted)
    {
        self.pOuterShape.transform = CGAffineTransformIdentity;
        m_currentAngleRadians = 0.0f;
        self.pOuterShape.image = m_pCompassDefaultImage;
    }
    
    for (CAShapeLayer *layer in self.pInnerShape.layer.sublayers)
    {
        [layer setStrokeColor:[[UIColor clearColor] CGColor]];
        [layer setFillColor:[[UIColor clearColor] CGColor]];
    }
}

- (void) showGpsFollowView
{
    m_compassViewState = Follow;
    
    if (!m_disabledStateHighlighted)
    {
        self.pOuterShape.image = m_pCompassLockedImage;
    }
}

- (void) showGpsCompassModeView
{
    m_compassViewState = Compass;
    
    if (!m_disabledStateHighlighted)
    {
        self.pOuterShape.image = m_pCompassUnlockedImage;
        self.pOuterShape.transform = CGAffineTransformIdentity;
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
    const CGAffineTransform rotateTransform = CGAffineTransformRotate(CGAffineTransformIdentity, -angleRadians);
    m_currentAngleRadians = angleRadians;
    self.pPoint.transform = CGAffineTransformTranslate(rotateTransform, 0, 0.f);
    if (m_compassViewState == Follow)
    {
        self.pOuterShape.transform = rotateTransform;
    }
    else
    {
        self.pOuterShape.transform = CGAffineTransformIdentity;
    }
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
    self.hidden = NO;
    
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
    
    if (onScreenState > 0.f)
    {
        self.hidden = false;
    }
    
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

- (void) setHighlighted:(BOOL)highlighted
{
    switch(m_compassViewState)
    {
        case Disabled:
            [self showGpsDisabledView];
            break;
        case Follow:
            [self showGpsFollowView];
            break;
        case Compass:
            [self showGpsCompassModeView];
            break;
        default:
            Eegeo_ASSERT(false, "Unhandled compass view state");
    }
    
    if(highlighted)
    {
        m_disabledStateHighlighted = true;
        
        if (m_compassViewState == Follow)
        {
            self.pOuterShape.image = m_pCompassLockedHighlightedImage;
        }
        else if (m_compassViewState == Disabled)
        {
            self.pOuterShape.image = m_pCompassDefaultHighlightImage;
        }
        else if (m_compassViewState == Compass)
        {
            self.pOuterShape.image = m_pCompassUnlockedHighlightedImage;
        }
    }
    else
    {
        m_disabledStateHighlighted = false;
        
        if (m_compassViewState == Follow)
        {
            self.pOuterShape.image = m_pCompassLockedImage;
        }
        else if (m_compassViewState == Disabled)
        {
            self.pOuterShape.image = m_pCompassDefaultImage;
        }
        else if (m_compassViewState == Compass)
        {
            self.pOuterShape.image = m_pCompassUnlockedImage;
        }
    }
}

- (void) setRotationHighlight:(bool)shouldShowRotationHighlight
{
    const float alpha = shouldShowRotationHighlight
        ? CompassOuterShapeActiveAlpha
        : CompassOuterShapeInactiveAlpha;
    [UIView animateWithDuration:RotationHighlightAnimationSeconds animations:^
     {
         self.pPoint.alpha = alpha;
     }];
}

@end

