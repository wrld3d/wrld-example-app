// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef APPRUNNER_H_
#define APPRUNNER_H_

#include "Thread.h"
#include "Graphics.h"
#include "AppHost.h"
#include "GlDisplayService.h"
#include "IMessageQueue.h"
#include "IAppMessage.h"
#include "ActiveObject.h"
#include "Types.h"
#include "FrameRateRegulator.h"
#include <algorithm>

class AppRunner :
	public Eegeo::Messaging::ActiveObject<const AppMessages::IAppMessage*, AppMessages::IAppMessageDispatcher>
{
public:
	AppRunner(
	    const std::string& apiKey,
	    AndroidNativeState* pNativeState,
	    AppToJavaProxy& appToJavaProxy
	);
	~AppRunner();

protected:
	void OnStarted();
	void OnStopped();
	void OnMessageHandled(const AppMessages::IAppMessage* message);
	void OnBeforeMessagesHandled();
	void OnAllMessagesHandled();

private:
	const std::string& m_apiKey;
	AndroidNativeState* m_pNativeState;
	AppToJavaProxy& m_appToJavaProxy;

	bool HandleMessage(const AppLifecycleMessages::AppPauseMessage& message);
	bool HandleMessage(const AppLifecycleMessages::AppDisplayAvailableMessage& message);
	bool HandleMessage(const InputMessages::TouchEventMessage& message);

	FrameRateRegulator m_frameRateRegulator;
	float m_deltaTime;

	GlDisplayService m_displayService;
	void ReleaseDisplay();
	bool TryBindDisplay();

	AppHost* m_pAppHost;
	void CreateAppHost();
};

#endif
