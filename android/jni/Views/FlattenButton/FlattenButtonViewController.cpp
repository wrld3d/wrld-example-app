// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FlattenButtonViewController.h"
#include "IFlattenButtonViewModel.h"
#include "IScreenControlViewModel.h"
#include "IFlattenButtonModel.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "FlattenButtonViewStateChangedMessage.h"

namespace ExampleApp
{
namespace FlattenButton
{
FlattenButtonViewController::FlattenButtonViewController(
    AndroidNativeState& nativeState,
    FlattenButton::IFlattenButtonViewModel& viewModel,
    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
	: m_nativeState(nativeState)
	, m_viewModel(viewModel)
	, m_uiToNativeMessageBus(uiToNativeMessageBus)
	, m_nativeToUiMessageBus(nativeToUiMessageBus)
	, m_flattenModelStateChangedCallback(this, &FlattenButtonViewController::OnFlattenModelStateChangedCallback)
	, m_pOnScreenStateChangedCallback(Eegeo_NEW((
	                                      Eegeo::Helpers::TCallback2<FlattenButtonViewController, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &FlattenButtonViewController::OnScreenStateChangedCallback))
{
	ASSERT_UI_THREAD

	m_nativeToUiMessageBus.Subscribe(m_flattenModelStateChangedCallback);
	m_viewModel.InsertOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	jstring strClassName = env->NewStringUTF("com.eegeo.flattenbutton.FlattenButtonView");
	jclass uiClass = m_nativeState.LoadClass(env, strClassName);
	env->DeleteLocalRef(strClassName);

	m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
	jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/mobileexampleapp/MainActivity;J)V");

	jobject instance = env->NewObject(
	                       m_uiViewClass,
	                       uiViewCtor,
	                       m_nativeState.activity,
	                       (jlong)(this)
	                   );

	m_uiView = env->NewGlobalRef(instance);
}

FlattenButtonViewController::~FlattenButtonViewController()
{
	ASSERT_UI_THREAD

	m_viewModel.RemoveOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
	m_nativeToUiMessageBus.Unsubscribe(m_flattenModelStateChangedCallback);

	Eegeo_DELETE m_pOnScreenStateChangedCallback;

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;
	jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
	env->CallVoidMethod(m_uiView, removeHudMethod);
	env->DeleteGlobalRef(m_uiView);
	env->DeleteGlobalRef(m_uiViewClass);
}

void FlattenButtonViewController::OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState)
{
	ASSERT_UI_THREAD

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	if(m_viewModel.IsFullyOnScreen())
	{
		jmethodID animateToClosedOnScreen = env->GetMethodID(m_uiViewClass, "animateToActive", "()V");
		env->CallVoidMethod(m_uiView, animateToClosedOnScreen);
	}
	else if (m_viewModel.IsFullyOffScreen())
	{
		jmethodID animateOffScreen = env->GetMethodID(m_uiViewClass, "animateToInactive", "()V");
		env->CallVoidMethod(m_uiView, animateOffScreen);
	}
	else
	{
		jmethodID animateToIntermediateOpenStateOnScreen = env->GetMethodID(m_uiViewClass, "animateToIntermediateOnScreenState", "(F)V");
		env->CallVoidMethod(m_uiView, animateToIntermediateOpenStateOnScreen, onScreenState);
	}
}

void FlattenButtonViewController::OnFlattenModelStateChangedCallback(const FlattenButtonModelStateChangedMessage& message)
{
	ASSERT_UI_THREAD

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	jmethodID updateViewStateBasedOnFlattening = env->GetMethodID(m_uiViewClass, "updateViewStateBasedOnFlattening", "(Z)V");
	env->CallVoidMethod(m_uiView, updateViewStateBasedOnFlattening, message.IsFlattened());
}

void FlattenButtonViewController::SetFlattened(bool flattened)
{
	ASSERT_UI_THREAD

	m_uiToNativeMessageBus.Publish(FlattenButtonViewStateChangedMessage(flattened));
}
}
}
