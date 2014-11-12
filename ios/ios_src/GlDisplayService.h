// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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

	bool IsDisplayAvailable() const;
	bool IsPortraitAspect() const;
	int GetDisplayWidth() const;
	int GetDisplayHeight() const;
	int GetDisplayDpi() const;
	int GetPixelScale() const;

private:
	int m_displayWidth;
	int m_displayHeight;
	int m_displayDpi;
	int m_pixelScale;
	bool m_displayBound;
	bool m_isPortraitAspect;
};

