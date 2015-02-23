// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppInputDelegate.h"
#include "ViewController.h"

#include <algorithm>

@implementation AppInputDelegateGestureListener

ViewController* m_pViewController;
AppInputDelegate* m_pAppInputDelegate;
float m_previousDist;
float m_pixelScale;
float m_screenWidth;
float m_screenHeight;

UIRotationGestureRecognizer *gestureRotation;
UIPinchGestureRecognizer *gesturePinch;
UIPanGestureRecognizer* gesturePan;
UITapGestureRecognizer* gestureTap;
UITapGestureRecognizer* gestureDoubleTap;
UILongPressGestureRecognizer* gestureTouch;

-(void) bindToViewController:(ViewController*)pViewController :(AppInputDelegate*)pAppInputDelegate :(float)width :(float)height :(float)pixelScale
{
    m_screenWidth = width;
    m_screenHeight = height;
    m_pixelScale = pixelScale;

    m_pViewController = pViewController;
    m_pAppInputDelegate = pAppInputDelegate;

    UIView* pView = [m_pViewController view];

    [pView setMultipleTouchEnabled: true];

    gestureRotation = [[UIRotationGestureRecognizer alloc] initWithTarget:self action:@selector(gestureRotation_Callback:)];
    [gestureRotation setDelegate:m_pViewController];
    gestureRotation.cancelsTouchesInView = FALSE;
    [pView addGestureRecognizer: gestureRotation];
    [gestureRotation release];

    gesturePinch = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(gesturePinch_Callback:)];
    [gesturePinch setDelegate:m_pViewController];
    gesturePinch.cancelsTouchesInView = FALSE;
    [pView addGestureRecognizer: gesturePinch];
    [gesturePinch release];

    gesturePan = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(gesturePan_Callback:)];
    [gesturePan setDelegate:m_pViewController];
    gesturePan.cancelsTouchesInView = FALSE;
    [pView addGestureRecognizer: gesturePan];
    [gesturePan release];

    gestureTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(gestureTap_Callback:)];
    [gestureTap setDelegate:m_pViewController];
    gestureTap.cancelsTouchesInView = FALSE;
    [pView addGestureRecognizer: gestureTap];
    [gestureTap release];

    gestureDoubleTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(gestureDoubleTap_Callback:)];
    [gestureDoubleTap setDelegate:m_pViewController];
    gestureDoubleTap.cancelsTouchesInView = FALSE;
    gestureDoubleTap.delaysTouchesEnded = FALSE;
    gestureDoubleTap.numberOfTapsRequired = 2;
    [pView addGestureRecognizer: gestureDoubleTap];
    [gestureDoubleTap release];

    gestureTouch = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(gestureTouch_Callback:)];
    [gestureTouch setDelegate:m_pViewController];
    gestureTouch.cancelsTouchesInView = FALSE;
    gestureTouch.minimumPressDuration = 0;
    [pView addGestureRecognizer: gestureTouch];
    [gestureTouch release];

}

-(void)gestureRotation_Callback:(UIRotationGestureRecognizer*)recognizer
{
    AppInterface::RotateData data;

    data.rotation	= static_cast<float>(recognizer.rotation);
    data.numTouches	= static_cast<int>(recognizer.numberOfTouches);
    data.velocity = static_cast<float>(recognizer.velocity);

    if (recognizer.state == UIGestureRecognizerStateBegan)
    {
        m_pAppInputDelegate->Event_TouchRotate_Start (data);
    }
    else if (recognizer.state == UIGestureRecognizerStateChanged)
    {
        m_pAppInputDelegate->Event_TouchRotate (data);
    }
    else if (recognizer.state == UIGestureRecognizerStateEnded)
    {
        m_pAppInputDelegate->Event_TouchRotate_End (data);
    }
}

namespace
{
    Eegeo::v2 CGPointToEegeoV2(const CGPoint& p)
    {
        return Eegeo::v2(static_cast<float>(p.x), static_cast<float>(p.y));
    }
}

-(void)gesturePinch_Callback:(UIPinchGestureRecognizer*)recognizer
{
    float dist;
    static bool reset = true;

    if (recognizer.numberOfTouches == 2)
    {
        CGPoint point0 = [recognizer locationOfTouch:0 inView:m_pViewController.view];
        CGPoint point1 = [recognizer locationOfTouch:1 inView:m_pViewController.view];

        Eegeo::v2 p0(CGPointToEegeoV2(point0));
        Eegeo::v2 p1(CGPointToEegeoV2(point1));

        Eegeo::v2 v2Dist = Eegeo::v2::Sub(p0, p1);

        dist = v2Dist.Length();

        if (reset)
        {
            m_previousDist = dist;
            reset = false;
        }
    }
    else
    {
        dist = m_previousDist;
        reset = true;
    }

    AppInterface::PinchData data;

    if (recognizer.state == UIGestureRecognizerStateBegan)
    {
        m_previousDist = dist;

        data.scale	= 0.0f;
        m_pAppInputDelegate->Event_TouchPinch_Start(data);

    }
    else if (recognizer.state == UIGestureRecognizerStateChanged)
    {
        float delta = (m_previousDist-dist);
        float majorScreenDimension = std::max(m_screenHeight, m_screenWidth);
        data.scale = delta/majorScreenDimension;
        m_pAppInputDelegate->Event_TouchPinch (data);
        m_previousDist = dist;
    }
    else if (recognizer.state == UIGestureRecognizerStateEnded)
    {
        data.scale	= static_cast<float>(recognizer.scale);
        m_pAppInputDelegate->Event_TouchPinch_End (data);
    }

    m_previousDist = dist;
}

-(Eegeo::v2)getGestureTouchExtents:(UIGestureRecognizer*)recognizer
{
    Eegeo::v2 touchExtents = Eegeo::v2::Zero();
    if (recognizer.numberOfTouches > 1)
    {
        CGPoint extentsMax = [recognizer locationOfTouch:0 inView:m_pViewController.view];
        CGPoint extentsMin = extentsMax;
        for (int i = 1; i < recognizer.numberOfTouches; ++i)
        {
            CGPoint point = [recognizer locationOfTouch:i inView:m_pViewController.view];
            extentsMax.x = std::max(extentsMax.x, point.x);
            extentsMax.y = std::max(extentsMax.y, point.y);
            extentsMin.x = std::min(extentsMin.x, point.x);
            extentsMin.y = std::min(extentsMin.y, point.y);
        }

        CGPoint extents = extentsMax;
        extents.x -= extentsMin.x;
        extents.y -= extentsMin.y;
        touchExtents = CGPointToEegeoV2(extents);
    }
    return touchExtents;
}

-(void)gesturePan_Callback:(UIPanGestureRecognizer*)recognizer
{
    CGPoint position = [recognizer translationInView:m_pViewController.view];
    CGPoint positionAbs = [recognizer locationInView:m_pViewController.view];
    CGPoint velocity = [recognizer velocityInView:m_pViewController.view];

    positionAbs.x *= m_pixelScale;
    positionAbs.y *= m_pixelScale;
    position.x *= m_pixelScale;
    position.y *= m_pixelScale;
    velocity.x *= m_pixelScale;
    velocity.y *= m_pixelScale;

    AppInterface::PanData data;

    data.pointRelative = CGPointToEegeoV2(position);
    float majorScreenDimension = std::max(m_screenHeight, m_screenWidth);
    data.pointRelativeNormalized = (data.pointRelative)/majorScreenDimension;
    data.pointAbsolute = CGPointToEegeoV2(positionAbs);
    data.velocity = CGPointToEegeoV2(velocity);
    data.majorScreenDimension = majorScreenDimension;
    data.numTouches = static_cast<int>(recognizer.numberOfTouches);
    data.touchExtents = [self getGestureTouchExtents :recognizer];

    if (recognizer.state == UIGestureRecognizerStateBegan)
    {
        m_pAppInputDelegate->Event_TouchPan_Start (data);
    }
    else if (recognizer.state == UIGestureRecognizerStateChanged)
    {
        m_pAppInputDelegate->Event_TouchPan (data);
    }
    else if (recognizer.state == UIGestureRecognizerStateEnded)
    {
        m_pAppInputDelegate->Event_TouchPan_End (data);
    }
}

-(void)gestureTap_Callback:(UITapGestureRecognizer*)recognizer
{
    if (recognizer.state == UIGestureRecognizerStateEnded)
    {
        CGPoint position = [recognizer locationInView:m_pViewController.view];

        position.x *= m_pixelScale;
        position.y *= m_pixelScale;

        AppInterface::TapData data;

        data.point = CGPointToEegeoV2(position);

        m_pAppInputDelegate->Event_TouchTap (data);

    }
}

-(void)gestureDoubleTap_Callback:(UITapGestureRecognizer*)recognizer
{
    if (recognizer.state == UIGestureRecognizerStateEnded)
    {
        CGPoint position = [recognizer locationInView:m_pViewController.view];

        position.x *= m_pixelScale;
        position.y *= m_pixelScale;

        AppInterface::TapData data;

        data.point = CGPointToEegeoV2(position);

        m_pAppInputDelegate->Event_TouchDoubleTap (data);

    }
}

-(void)gestureTouch_Callback:(UILongPressGestureRecognizer*)recognizer
{
    AppInterface::TouchData data;

    CGPoint position = [recognizer locationInView:m_pViewController.view];
    position.x *= m_pixelScale;
    position.y *= m_pixelScale;
    data.point	= CGPointToEegeoV2(position);

    if(recognizer.state == UIGestureRecognizerStateBegan)
    {
        m_pAppInputDelegate->Event_TouchDown(data);
    }
    else if(recognizer.state == UIGestureRecognizerStateChanged)
    {
        m_pAppInputDelegate->Event_TouchMove(data);
    }
    else if(recognizer.state == UIGestureRecognizerStateEnded)
    {
        m_pAppInputDelegate->Event_TouchUp(data);
    }
}

@end

AppInputDelegate::AppInputDelegate(
    ExampleApp::MobileExampleApp& exampleApp,
    ViewController& viewController,
    float width,
    float height,
    float pixelScale
)
    :m_exampleApp(exampleApp)
{
    m_pAppInputDelegateGestureListener = [[AppInputDelegateGestureListener alloc] init];
    [m_pAppInputDelegateGestureListener bindToViewController:&viewController :this :width :height :pixelScale];
}

AppInputDelegate::~AppInputDelegate()
{
    [m_pAppInputDelegateGestureListener release];
    m_pAppInputDelegateGestureListener = nil;
}

void AppInputDelegate::Event_TouchRotate(const AppInterface::RotateData& data)
{
    m_exampleApp.Event_TouchRotate(data);
}

void AppInputDelegate::Event_TouchRotate_Start(const AppInterface::RotateData& data)
{
    m_exampleApp.Event_TouchRotate_Start(data);
}

void AppInputDelegate::Event_TouchRotate_End(const AppInterface::RotateData& data)
{
    m_exampleApp.Event_TouchRotate_End(data);
}

void AppInputDelegate::Event_TouchPinch(const AppInterface::PinchData& data)
{
    m_exampleApp.Event_TouchPinch(data);
}

void AppInputDelegate::Event_TouchPinch_Start(const AppInterface::PinchData& data)
{
    m_exampleApp.Event_TouchPinch_Start(data);
}

void AppInputDelegate::Event_TouchPinch_End(const AppInterface::PinchData& data)
{
    m_exampleApp.Event_TouchPinch_End(data);
}

void AppInputDelegate::Event_TouchPan(const AppInterface::PanData& data)
{
    m_exampleApp.Event_TouchPan(data);
}

void AppInputDelegate::Event_TouchPan_Start(const AppInterface::PanData& data)
{
    m_exampleApp.Event_TouchPan_Start(data);
}

void AppInputDelegate::Event_TouchPan_End(const AppInterface::PanData& data)
{
    m_exampleApp.Event_TouchPan_End(data);
}

void AppInputDelegate::Event_TouchTap(const AppInterface::TapData& data)
{
    m_exampleApp.Event_TouchTap(data);
}

void AppInputDelegate::Event_TouchDoubleTap(const AppInterface::TapData& data)
{
    m_exampleApp.Event_TouchDoubleTap(data);
}

void AppInputDelegate::Event_TouchDown(const AppInterface::TouchData& data)
{
    m_exampleApp.Event_TouchDown(data);
}

void AppInputDelegate::Event_TouchMove(const AppInterface::TouchData& data)
{
    m_exampleApp.Event_TouchMove(data);
}

void AppInputDelegate::Event_TouchUp(const AppInterface::TouchData& data)
{
    m_exampleApp.Event_TouchUp(data);
}

