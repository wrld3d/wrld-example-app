// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GlDisplayService.h"
#include "App.h"

#include <algorithm>

GlDisplayService::GlDisplayService()
    : m_displayWidth(0)
    , m_displayHeight(0)
    , m_displayDpi(0)
    , m_pixelScale(0)
    , m_displayBound(false)
    , m_isPortraitAspect(false)
{

}

GlDisplayService::~GlDisplayService()
{
    ReleaseDisplay();
}

bool GlDisplayService::IsDisplayAvailable() const
{
    return m_displayBound;
}

float GlDisplayService::GetDisplayWidth() const
{
    return m_displayWidth;
}

float GlDisplayService::GetDisplayHeight() const
{
    return m_displayHeight;
}

float GlDisplayService::GetDisplayDpi() const
{
    return m_displayDpi;
}

float GlDisplayService::GetPixelScale() const
{
    return m_pixelScale;
}

bool GlDisplayService::IsPortraitAspect() const
{
    return m_isPortraitAspect;
}

bool GlDisplayService::TryBindDisplay(GLKView& view)
{
    App::Initialise();

    GLKViewDrawableMultisample multiSample;

    if (App::IsDeviceSmall())
    {
        // AA on for high-performance small devices (phones >= GAME_DEVICE_IPHONE4S, ipods >= GAME_DEVICE_IPOD5)
        multiSample = App::IsDeviceMultiCore() ? GLKViewDrawableMultisample4X : GLKViewDrawableMultisampleNone;
    }
    else
    {
        // AA on for GAME_DEVICE_IPAD2 / GAME_DEVICE_IPADMINI_1GEN
        multiSample = (App::IsDeviceMultiCore() && !App::HasRetinaDisplay()) ? GLKViewDrawableMultisample4X : GLKViewDrawableMultisampleNone;
    }

    GLKView* pView =  &view;//(GLKView*)((UIViewController*)self).view;

    // Create an OpenGLES2 context and store.
    pView.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (pView.context == nil)
    {
        NSLog(@"Graphics(): Error - Failed to create ES context");
    }

    // Set the default values for the screen, depth and stencil buffers.
    pView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    pView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    pView.drawableStencilFormat = GLKViewDrawableStencilFormat8;
    pView.drawableMultisample = multiSample;

    [EAGLContext setCurrentContext: pView.context];

    m_displayBound = true;

    UpdateDisplayDimensions();

    return m_displayBound;
}

void GlDisplayService::UpdateDisplayDimensions()
{
    Eegeo_ASSERT(m_displayBound, "GlDisplayService::UpdateDisplayDimensions - display not bound");

    UIScreen* screen = [UIScreen mainScreen];
    if ([screen respondsToSelector: @selector(scale)])
    {
        m_pixelScale = static_cast<float>(screen.scale);
    }
    else
    {
        m_pixelScale = 1.f;
    }

    CGSize screenBounds;

    if ([screen respondsToSelector:@selector(fixedCoordinateSpace)])
    {
        screenBounds = [screen.coordinateSpace convertRect:screen.bounds toCoordinateSpace:screen.fixedCoordinateSpace].size;
    }
    else
    {
        screenBounds = screen.bounds.size;
    }

    OrientationMode orientationMode = App::DetermineOrientationMode();

    // default to landscape if we were not able to query info.plist (orientationMode == ORIENTATION_MODE_UNKNOWN)
    m_isPortraitAspect = (orientationMode == ORIENTATION_MODE_PORTRAIT);

    if (!m_isPortraitAspect)
    {
        std::swap(screenBounds.width, screenBounds.height);
    }

    m_displayWidth = static_cast<float>(screenBounds.width * m_pixelScale);
    m_displayHeight = static_cast<float>(screenBounds.height * m_pixelScale);
    m_displayDpi = App::GetDeviceDpi() * m_pixelScale;
}

void GlDisplayService::ReleaseDisplay()
{
    m_displayBound = false;
}




