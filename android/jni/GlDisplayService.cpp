// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GlDisplayService.h"
#include "Logger.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidNativeState.h"

GlDisplayService::GlDisplayService()
    : m_display(EGL_NO_DISPLAY)
    , m_surface(EGL_NO_SURFACE)
    , m_sharedSurface(EGL_NO_SURFACE)
    , m_context(EGL_NO_CONTEXT)
    , m_resourceBuildSharedContext(EGL_NO_CONTEXT)
    , m_displayBound(false)
{
    ASSERT_NATIVE_THREAD

    m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(m_display, 0, 0);
}

GlDisplayService::~GlDisplayService()
{
    ASSERT_NATIVE_THREAD

    bool destroyEGL = true;
    ReleaseDisplay(destroyEGL);
}

bool GlDisplayService::IsDisplayAvailable() const
{
    ASSERT_NATIVE_THREAD

    return m_displayBound;
}

int GlDisplayService::GetDisplayWidth() const
{
    ASSERT_NATIVE_THREAD

    return m_displayWidth;
}

int GlDisplayService::GetDisplayHeight() const
{
    ASSERT_NATIVE_THREAD

    return m_displayHeight;
}

EGLDisplay GlDisplayService::GetDisplay() const
{
    ASSERT_NATIVE_THREAD

    return m_display;
}

EGLSurface GlDisplayService::GetSurface() const
{
    ASSERT_NATIVE_THREAD

    return m_surface;
}

EGLSurface GlDisplayService::GetSharedSurface() const
{
    ASSERT_NATIVE_THREAD

    return m_sharedSurface;
}

EGLContext GlDisplayService::GetContext() const
{
    ASSERT_NATIVE_THREAD

    return m_context;
}

EGLContext GlDisplayService::GetResourceBuildSharedContext() const
{
    ASSERT_NATIVE_THREAD

    return m_resourceBuildSharedContext;
}

namespace
{
// based on nVidia example app for Tegra
    bool DefaultEGLChooser(EGLDisplay disp, u32 requestedSurfaceType, EGLConfig& bestConfig)
    {
        ASSERT_NATIVE_THREAD

        EGLint count = 0;
        if (!eglGetConfigs(disp, NULL, 0, &count))
        {
            EXAMPLE_LOG("defaultEGLChooser cannot query count of all configs");
            return false;
        }

        EXAMPLE_LOG("Config count = %d", count);

        EGLConfig* configs = Eegeo_ARRAY_NEW(EGLConfig, count);
        if (!eglGetConfigs(disp, configs, count, &count))
        {
            EXAMPLE_LOG("defaultEGLChooser cannot query all configs");
            return false;
        }

        int bestMatch = 1<<30;
        int bestIndex = -1;

        int i;
        for (i = 0; i < count; i++)
        {
            int match = 0;
            EGLint surfaceType = 0;
            EGLint blueBits = 0;
            EGLint greenBits = 0;
            EGLint redBits = 0;
            EGLint alphaBits = 0;
            EGLint depthBits = 0;
            EGLint stencilBits = 0;
            EGLint renderableFlags = 0;

            eglGetConfigAttrib(disp, configs[i], EGL_SURFACE_TYPE, &surfaceType);
            eglGetConfigAttrib(disp, configs[i], EGL_BLUE_SIZE, &blueBits);
            eglGetConfigAttrib(disp, configs[i], EGL_GREEN_SIZE, &greenBits);
            eglGetConfigAttrib(disp, configs[i], EGL_RED_SIZE, &redBits);
            eglGetConfigAttrib(disp, configs[i], EGL_ALPHA_SIZE, &alphaBits);
            eglGetConfigAttrib(disp, configs[i], EGL_DEPTH_SIZE, &depthBits);
            eglGetConfigAttrib(disp, configs[i], EGL_STENCIL_SIZE, &stencilBits);
            eglGetConfigAttrib(disp, configs[i], EGL_RENDERABLE_TYPE, &renderableFlags);


            if ((surfaceType & requestedSurfaceType) == 0)
                continue;
            if ((renderableFlags & EGL_OPENGL_ES2_BIT) == 0)
                continue;

            if (depthBits < 16)
                continue;
            if ((redBits < 5) || (greenBits < 6) || (blueBits < 5))
                continue;
            if (stencilBits < 8)
                continue;

            int penalty = depthBits - 16;
            match += penalty * penalty;
            penalty = redBits - 5;
            match += penalty * penalty;
            penalty = greenBits - 6;
            match += penalty * penalty;
            penalty = blueBits - 5;
            match += penalty * penalty;
            penalty = alphaBits;
            match += penalty * penalty;
            penalty = stencilBits - 8;
            match += penalty * penalty;

            if ((match < bestMatch) || (bestIndex == -1))
            {
                bestMatch = match;
                bestIndex = i;
                EXAMPLE_LOG("New best Config[%d]: R%dG%dB%dA%d D%dS%d Type=%04x Render=%04x",
                            i, redBits, greenBits, blueBits, alphaBits, depthBits, stencilBits, surfaceType, renderableFlags);
            }
        }

        if (bestIndex < 0)
        {
            Eegeo_ARRAY_DELETE configs;
            return false;
        }

        bestConfig = configs[bestIndex];
        Eegeo_ARRAY_DELETE configs;

        EXAMPLE_LOG("Found a valid config.");
        return true;
    }
}

bool GlDisplayService::TryBindDisplay(ANativeWindow& window)
{
    ASSERT_NATIVE_THREAD

    EGLint w, h, format;
    EGLConfig config;
    EGLSurface surface;

    if (!DefaultEGLChooser(m_display, EGL_WINDOW_BIT, config))
    {
    	EXAMPLE_LOG("Unable to bind display. Couldn't find a good display type. DefaultEGLChooser failed");
        return false;
    }

    if(!eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format))
    {
    	EXAMPLE_LOG("Unable to bind display. Couldn't find a good display type, eglGetConfigAttrib failed");
    	return false;
    }

    // no documentation on what return code means. Some other functions return a negative value to indicate failure.

    ANativeWindow_setBuffersGeometry(&window, 0, 0, format);

    static const EGLint contextAttribs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION,
        2,
        EGL_NONE
    };

    surface = eglCreateWindowSurface(m_display, config, &window, NULL);
    if(surface == EGL_NO_SURFACE)
    {
    	EXAMPLE_LOG("Unable to bind display. eglCreateWindowSurface failed.");
    	return false;
    }

    if(m_context == EGL_NO_CONTEXT)
    {
		EXAMPLE_LOG("m_context == EGL_NO_CONTEXT. Creating context...");
        m_context = eglCreateContext(m_display, config, NULL, contextAttribs);     
    }
	
	if(m_context == EGL_NO_CONTEXT)
	{
		EXAMPLE_LOG("Unable to bind display. eglCreateContext failed");
		return false;
	}

    if (eglMakeCurrent(m_display, surface, surface, m_context) == EGL_FALSE)
    {
    	EXAMPLE_LOG("Unable to eglMakeCurrent");
        return false;
    }

    //EXAMPLE_LOG("printing extensions\n");
    //char * extensionsString =  (char *) glGetString(GL_EXTENSIONS);
    //EXAMPLE_LOG("%s\n",extensionsString);

    Eegeo_GL(eglQuerySurface(m_display, surface, EGL_WIDTH, &w));
    Eegeo_GL(eglQuerySurface(m_display, surface, EGL_HEIGHT, &h));

    m_surface = surface;

#ifdef EEGEO_DROID_EMULATOR
    m_sharedSurface = EGL_NO_SURFACE;
    m_resourceBuildSharedContext = EGL_NO_CONTEXT;
#else
    EGLint pBufferAttribs[] =
    {
        EGL_WIDTH, 1,
        EGL_HEIGHT, 1,
        EGL_TEXTURE_TARGET, EGL_NO_TEXTURE,
        EGL_TEXTURE_FORMAT, EGL_NO_TEXTURE,
        EGL_NONE
    };
    EGLConfig sharedSurfaceConfig;
    if (!DefaultEGLChooser(m_display, EGL_PBUFFER_BIT, sharedSurfaceConfig))
    {
    	EXAMPLE_LOG("Unable to bind display. Couldn't find a good pbuffer surface type, called DefaultEGLChoose with EGL_PBUFFER_BIT and it failed.");
        return false;
    }

    if(m_resourceBuildSharedContext == EGL_NO_CONTEXT)
    {
        m_resourceBuildSharedContext = eglCreateContext(m_display, sharedSurfaceConfig, m_context, contextAttribs);
        if(m_resourceBuildSharedContext == EGL_NO_CONTEXT)
        {
        	EXAMPLE_LOG("Unable to bind display. eglCreateContext failed for shared surface config.");
        	return false;
        }
    }

    m_sharedSurface = eglCreatePbufferSurface(m_display, sharedSurfaceConfig, pBufferAttribs);
    if(m_sharedSurface == EGL_NO_SURFACE)
    {
    	EXAMPLE_LOG("Unable to bind display. eglCreatePbufferSurface failed with shared surface config.");
    	return false;
    }
#endif

    m_displayWidth = w;
    m_displayHeight = h;

    glViewport(0, 0, m_displayWidth, m_displayHeight);

    // Initialize GL state.
    Eegeo_GL(glClearDepthf(1.0f));
    Eegeo_GL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

    // Set up default Depth test.
    Eegeo_GL(glEnable(GL_DEPTH_TEST));
    Eegeo_GL(glDepthMask(GL_TRUE));
    Eegeo_GL(glDepthFunc(GL_LEQUAL));

    // Set up default culling.
    Eegeo_GL(glEnable(GL_CULL_FACE));
    Eegeo_GL(glFrontFace(GL_CW));
    Eegeo_GL(glCullFace(GL_BACK));

    // Turn off the stencil test.
    Eegeo_GL(glDisable(GL_STENCIL_TEST));
    Eegeo_GL(glStencilFunc(GL_NEVER, 0, 0xFFFFFFFF));
    Eegeo_GL(glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP));

    // Set the default blend mode and colour mask.
    Eegeo_GL(glDisable(GL_BLEND));
    Eegeo_GL(glColorMask(true, true, true, true));

    Eegeo_GL(glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

    eglSwapInterval(m_display, 1);

    m_displayBound = true;

    return m_displayBound;
}

void GlDisplayService::ReleaseDisplay(bool destroyEGL)
{
    ASSERT_NATIVE_THREAD

    if (m_display != EGL_NO_DISPLAY)
    {
        Eegeo_GL(eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));

        if (m_surface != EGL_NO_SURFACE)
        {
            Eegeo_GL(eglDestroySurface(m_display, m_surface));
        }

        if (m_sharedSurface != EGL_NO_SURFACE)
        {
            Eegeo_GL(eglDestroySurface(m_display, m_sharedSurface));
        }

        if(destroyEGL)
        {
            if (m_context != EGL_NO_CONTEXT)
            {
                Eegeo_GL(eglDestroyContext(m_display, m_context));
            }

            if(m_resourceBuildSharedContext != EGL_NO_CONTEXT)
            {
                Eegeo_GL(eglDestroyContext(m_display, m_resourceBuildSharedContext));
            }

            Eegeo_GL(eglTerminate(m_display));

            m_display = EGL_NO_DISPLAY;
            m_context = EGL_NO_CONTEXT;
            m_resourceBuildSharedContext = EGL_NO_CONTEXT;
        }
    }

    m_surface = EGL_NO_SURFACE;
    m_sharedSurface = EGL_NO_SURFACE;

    m_displayBound = false;
}
