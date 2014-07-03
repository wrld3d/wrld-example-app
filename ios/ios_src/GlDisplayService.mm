// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "GlDisplayService.h"
#include "App.h"

GlDisplayService::GlDisplayService()
    : m_displayBound(false)
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

int GlDisplayService::GetDisplayWidth() const
{
	return m_displayWidth;
}

int GlDisplayService::GetDisplayHeight() const
{
	return m_displayHeight;
}

int GlDisplayService::GetDisplayDpi() const
{
	return m_displayDpi;
}

int GlDisplayService::GetPixelScale() const
{
	return m_pixelScale;
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
    
    m_pixelScale = 1.f;
    
	float width 		= pView.bounds.size.width * m_pixelScale;
	float height 		= pView.bounds.size.height * m_pixelScale;
    
	bool boPortrait = App::IsDeviceSmall();
    
	if (!boPortrait)
	{
		float temp = width;
		width = height;
		height = temp;
	}
    
    
    m_displayWidth = width;
    m_displayHeight = height;
    m_displayDpi = App::GetDeviceDpi() * m_pixelScale;

	m_displayBound = true;
	return m_displayBound;
}

void GlDisplayService::ReleaseDisplay()
{
	m_displayBound = false;
}




