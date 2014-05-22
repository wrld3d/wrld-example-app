//  Copyright (c) 2014 eeGeo. All rights reserved.

#ifndef NATIVETOJAVAMESSAGEBUS_H_
#define NATIVETOJAVAMESSAGEBUS_H_

#include "Types.h"
#include "AndroidNativeState.h"
#include "AppToJavaMessages.h"
#include "IAppToJavaMessageDispatcher.h"
#include "IAppToJavaMessage.h"
#include "ActiveObject.h"
#include <JNI.h>

extern "C"
{
    JNIEXPORT long JNICALL Java_com_eegeo_NativeToJavaMessagePump_pumpNativeMessageQueue(JNIEnv* jenv, jobject obj, jlong nativeHandler);
}

class AppToJavaHandler :
	public Eegeo::Messaging::ActiveObject<const AppMessages::AppToJava::IAppToJavaMessage*,
										  AppMessages::AppToJava::IAppToJavaMessageDispatcher>
{
public:
	AppToJavaHandler(
			AndroidNativeState& nativeState,
			jobject& nativeToJavaMessageHandler,
			jobject& mainActivity
			);
	virtual ~AppToJavaHandler();

	void SignalMessageAvailable();

private:
	AndroidNativeState& m_nativeState;
	jobject& m_nativeToJavaMessageHandler;
	jobject& m_mainActivity;
	jmethodID m_messageAvailableHandlerMethodId;
	jmethodID m_onModeStartedMethodId;
};

#endif /* NATIVETOJAVAMESSAGEBUS_H_ */
