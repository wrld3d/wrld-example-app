// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <GLKit/GLKit.h>
#import <UIKit/UIKit.h>
#include "Types.h"
#include "Graphics.h"

class GlDisplayService
{
public:
    GlDisplayService();
    ~GlDisplayService();

    bool TryBindDisplay(GLKView& view);
    void ReleaseDisplay();
    void UpdateDisplayDimensions();

    bool IsDisplayAvailable() const;
    bool IsPortraitAspect() const;
    float GetDisplayWidth() const;
    float GetDisplayHeight() const;
    float GetDisplayDpi() const;
    float GetPixelScale() const;

private:
    float m_displayWidth;
    float m_displayHeight;
    float m_displayDpi;
    float m_pixelScale;
    bool m_displayBound;
    bool m_isPortraitAspect;
};

