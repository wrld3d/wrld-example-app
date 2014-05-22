//  Copyright (c) 2014 eeGeo. All rights reserved.

#include "Types.h"
#include "AppProxy.h"
#include "AppRunner.h"
#include "TouchEventMessage.h"
#include "AppPauseMessage.h"
#include "AppDisplayAvailableMessage.h"

AppProxy::AppProxy(AppRunner& appRunner)
: m_appRunner(appRunner)
, m_thread(appRunner)
{
}

AppProxy::~AppProxy()
{
	Eegeo_TTY("Destroy app proxy %d\n", m_thread.IsRunning());
}

void AppProxy::Pause()
{
	Eegeo_TTY("Attempt pause\n");

	AppLifecycleMessages::AppPauseMessage* pMessage = Eegeo_NEW(AppLifecycleMessages::AppPauseMessage)();
	m_appRunner.SendMessage(pMessage);
	m_thread.WaitForStop();

	Eegeo_TTY("Done pause\n");
}

void AppProxy::Resume()
{
	Eegeo_TTY("Resume\n");

	m_thread.Start();
}

void AppProxy::ActivateSurface()
{
	AppLifecycleMessages::AppDisplayAvailableMessage* pMessage = Eegeo_NEW(AppLifecycleMessages::AppDisplayAvailableMessage)();
	m_appRunner.SendMessage(pMessage);
}

void AppProxy::SendTouchEvent(const InputMessages::TouchEventMessage* pTouchEvent)
{
	m_appRunner.SendMessage(pTouchEvent);
}


