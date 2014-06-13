// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef APPPROXY_H_
#define APPPROXY_H_

#include "AppRunner.h"
#include "InputMessages.h"
#include "Thread.h"

class AppProxy
{
public:
	AppProxy(AppRunner& appRunner);
	~AppProxy();

	void Pause();
	void Resume();
	void ActivateSurface();

	void SendTouchEvent(const InputMessages::TouchEventMessage* pTouchEvent);

private:
	AppRunner& m_appRunner;
	Eegeo::Concurrency::Thread m_thread;
};

#endif
