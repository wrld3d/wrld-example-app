// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef APPRUNNER_H_
#define APPRUNNER_H_

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
	    const std::string& apiKey,
        ViewController& pView
    );
	~AppRunner();

	void Pause();
	void Resume();
	void Update(float deltaSeconds);
    bool ShouldAutoRotateToInterfaceOrientation(UIInterfaceOrientation interfaceOrientation);

private:
    ViewController& m_viewController;
	const std::string& m_apiKey;

	GlDisplayService m_displayService;
	void ReleaseDisplay();
	bool TryBindDisplay();

	AppHost* m_pAppHost;
	void CreateAppHost();
};

#endif
