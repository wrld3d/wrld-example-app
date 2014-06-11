//  Copyright (c) 2014 eeGeo. All rights reserved.

#include "AppRunner.h"
#include "Graphics.h"
#include "AndroidThreadHelper.h"
#include "AppDisplayAvailableMessage.h"
#include "TouchEventMessage.h"

AppRunner::AppRunner
(
    const std::string& apiKey,
    AndroidNativeState* pNativeState,
    AppToJavaProxy& appToJavaProxy
)
	: m_apiKey(apiKey)
	, m_pNativeState(pNativeState)
	, m_frameRateRegulator(30)
	, m_deltaTime(1/30.0f)
	, m_pAppHost(NULL)
	, m_appToJavaProxy(appToJavaProxy)
{
}

AppRunner::~AppRunner()
{
	bool destroyEGL = true;
	m_displayService.ReleaseDisplay(destroyEGL);

	if(m_pAppHost != NULL)
	{
		Eegeo_DELETE(m_pAppHost);
	}
}

void AppRunner::OnStarted()
{
	Eegeo::Helpers::ThreadHelpers::SetThisThreadAsMainThread();

	if(m_pAppHost != NULL)
	{
		m_pAppHost->OnResume();
	}
}

void AppRunner::OnStopped()
{
	if(m_pAppHost != NULL)
	{
		m_pAppHost->OnPause();
	}
}

bool AppRunner::HandleMessage(const AppLifecycleMessages::AppPauseMessage& message)
{
	ReleaseDisplay();

	const bool continueRunning = false;
	return continueRunning;
}

bool AppRunner::HandleMessage(const AppLifecycleMessages::AppDisplayAvailableMessage& message)
{
	ReleaseDisplay();

	if(!TryBindDisplay())
	{
		SendMessage(&message);
	}

	CreateAppHost();

	const bool continueRunning = true;
	return continueRunning;
}

bool AppRunner::HandleMessage(const InputMessages::TouchEventMessage& message)
{
	if(m_pAppHost != NULL)
	{
		m_pAppHost->HandleTouchInputEvent(message.GetTouchInputEvent());
	}

	const bool continueRunning = true;
	return continueRunning;
}

void AppRunner::ReleaseDisplay()
{
	if(m_displayService.IsDisplayAvailable())
	{
		const bool teardownEGL = false;
		m_displayService.ReleaseDisplay(teardownEGL);
	}
}

bool AppRunner::TryBindDisplay()
{
	if(m_displayService.TryBindDisplay(*(m_pNativeState->window)))
	{
		if(m_pAppHost != NULL)
		{
			m_pAppHost->SetSharedSurface(m_displayService.GetSharedSurface());
			m_pAppHost->SetViewportOffset(0, 0);
		}

		return true;
	}

	return false;
}

void AppRunner::CreateAppHost()
{
	if(m_pAppHost == NULL && m_displayService.IsDisplayAvailable())
	{
		m_pAppHost = Eegeo_NEW(AppHost)
		             (
		                 m_apiKey,
		                 *m_pNativeState,
		                 m_displayService.GetDisplayWidth(),
		                 m_displayService.GetDisplayHeight(),
		                 m_displayService.GetDisplay(),
		                 m_displayService.GetSharedSurface(),
		                 m_displayService.GetResourceBuildSharedContext(),
		                 m_appToJavaProxy
		             );
	}
}

void AppRunner::OnBeforeMessagesHandled()
{
	m_deltaTime = m_frameRateRegulator.WaitForFrameStart();
}

void AppRunner::OnAllMessagesHandled()
{
	if(m_pAppHost != NULL && m_displayService.IsDisplayAvailable())
	{
		m_pAppHost->Update(m_deltaTime);

		Eegeo_GL(eglSwapBuffers(m_displayService.GetDisplay(), m_displayService.GetSurface()));
		Eegeo_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

		m_pAppHost->Draw(m_deltaTime);
	}
}

void AppRunner::OnMessageHandled(const AppMessages::IAppMessage* message)
{
	Eegeo_DELETE(message);
}





