//  Copyright (c) 2014 eeGeo. All rights reserved.

#include "AppToJavaHandler.h"

JNIEXPORT long JNICALL Java_com_eegeo_NativeToJavaMessagePump_pumpNativeMessageQueue(JNIEnv* jenv, jobject obj, jlong nativeHandler)
{
	((AppToJavaHandler*)nativeHandler)->ProcessMessages();
}

AppToJavaHandler::AppToJavaHandler(
    AndroidNativeState& nativeState,
    jobject& nativeToJavaMessageHandler,
    jobject& mainActivity)
	: m_nativeState(nativeState)
	, m_nativeToJavaMessageHandler(nativeToJavaMessageHandler)
	, m_mainActivity(mainActivity)
{
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* pEnv = attached.envForThread;

	jclass nativeToJavaMessageHandlerClass = pEnv->GetObjectClass(m_nativeToJavaMessageHandler);
	m_messageAvailableHandlerMethodId = pEnv->GetMethodID(nativeToJavaMessageHandlerClass, "handleMessage", "(J)V");
}

AppToJavaHandler::~AppToJavaHandler()
{
}

void AppToJavaHandler::SignalMessageAvailable()
{
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* pEnv = attached.envForThread;

	pEnv->CallVoidMethod(m_nativeToJavaMessageHandler, m_messageAvailableHandlerMethodId, (jlong) this);
}
