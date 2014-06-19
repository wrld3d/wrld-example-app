// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AppRunner.h"
#include "Graphics.h"
#include "AndroidThreadHelper.h"

AppRunner::AppRunner
(
    const std::string& apiKey,
    AndroidNativeState* pNativeState
)
	: m_apiKey(apiKey)
	, m_pNativeState(pNativeState)
	, m_pAppHost(NULL)
{
	Eegeo::Helpers::ThreadHelpers::SetThisThreadAsMainThread();
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
		                 m_displayService.GetResourceBuildSharedContext()
		             );
	}
}

void AppRunner::Pause()
{
	if(m_pAppHost != NULL)
	{
		m_pAppHost->OnPause();
	}

	ReleaseDisplay();
}

void AppRunner::Resume()
{
	if(m_pAppHost != NULL)
	{
		m_pAppHost->OnResume();
	}
}

void AppRunner::ActivateSurface()
{
	ReleaseDisplay();
	bool displayBound = TryBindDisplay();
	Eegeo_ASSERT(displayBound);
	CreateAppHost();
}

void AppRunner::HandleTouchEvent(const Eegeo::Android::Input::TouchInputEvent& event)
{
	if(m_pAppHost != NULL)
	{
		m_pAppHost->HandleTouchInputEvent(event);
	}
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

void AppRunner::Update(float deltaSeconds)
{
	if(m_pAppHost != NULL && m_displayService.IsDisplayAvailable())
	{
		m_pAppHost->Update(deltaSeconds);

		Eegeo_GL(eglSwapBuffers(m_displayService.GetDisplay(), m_displayService.GetSurface()));
		Eegeo_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

		m_pAppHost->Draw(deltaSeconds);
	}
}


