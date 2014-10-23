// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "Graphics.h"
#include "AppHost.h"
#include "GlDisplayService.h"
#include "Types.h"

@class ViewController;

class AppRunner : Eegeo::NonCopyable
{
public:
	AppRunner(
              ViewController& pViewController,
              UIView* pView
              );
	~AppRunner();
    
    bool IsRunning();
    
	void Pause();
	void Resume();
	void Update(float deltaSeconds);
    
    bool ShouldAutoRotateToInterfaceOrientation(UIInterfaceOrientation interfaceOrientation);
    
private:
    ViewController& m_viewController;
    UIView* m_pView;
    
	GlDisplayService m_displayService;
	void ReleaseDisplay();
	bool TryBindDisplay();
    
	AppHost* m_pAppHost;
	void CreateAppHost();
};

