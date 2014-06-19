/*
 * AndroidExampleControllerView.cpp
 */

#include "AndroidExampleControllerView.h"
#include "UIHelpers.h"
#include "AndroidExampleControllerProxy.h"
#include <jni.h>

using namespace Examples;

namespace Examples
{
AndroidExampleControllerView::AndroidExampleControllerView(
    AndroidNativeState& androidNativeState)
	: m_nativeState(androidNativeState)
{
	//get an env for the current thread
	//
	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//get the java RouteMatchingExampleHud class
	jstring strClassName = env->NewStringUTF("com/eegeo/examples/ExampleControllerHud");
	jclass routeMatchingExampleHudClass = m_nativeState.LoadClass(env, strClassName);
	env->DeleteLocalRef(strClassName);

	//create a persistent reference to the class
	m_androidExampleControllerViewClass = static_cast<jclass>(env->NewGlobalRef(routeMatchingExampleHudClass));

	//get the constructor for the ExampleControllerHud, which takes the activity, a pointer to 'this' as
	//a parameter, and a flag to indicate if currently in follow mode.
	jmethodID exampleControllerHudConstructor = env->GetMethodID(routeMatchingExampleHudClass, "<init>", "(Lcom/eegeo/MainActivity;J)V");

	jobject instance = env->NewObject(
	                       m_androidExampleControllerViewClass,
	                       exampleControllerHudConstructor,
	                       m_nativeState.activity,
	                       (jlong)(this));

	m_androidExampleControllerView = env->NewGlobalRef(instance);
}

AndroidExampleControllerView::~AndroidExampleControllerView()
{
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//Get a reference to the 'removeHud' method and call it to remove the HUD.
	jmethodID removeHudMethod = env->GetMethodID(m_androidExampleControllerViewClass, "removeHud", "()V");
	env->CallVoidMethod(m_androidExampleControllerView, removeHudMethod);

	//Destroy the cached global references.
	env->DeleteGlobalRef(m_androidExampleControllerView);
	env->DeleteGlobalRef(m_androidExampleControllerViewClass);
}

void AndroidExampleControllerView::Show()
{
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	jmethodID showButtons = env->GetMethodID(m_androidExampleControllerViewClass, "showViews", "()V");

	env->CallVoidMethod(
	    m_androidExampleControllerView,
	    showButtons);
}

void AndroidExampleControllerView::PopulateExampleList(const std::vector<std::string>& exampleNames)
{
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	jstring strClassName = env->NewStringUTF("java/lang/String");
	jclass strClass = m_nativeState.LoadClass(env, strClassName);
	jobjectArray stringArray = env->NewObjectArray(exampleNames.size(), strClass, 0);

	for(size_t i = 0; i < exampleNames.size(); ++ i)
	{
		jstring exampleNameJni = env->NewStringUTF(exampleNames[i].c_str());
		env->SetObjectArrayElement(stringArray, i, exampleNameJni);
		env->DeleteLocalRef(exampleNameJni);
	}

	jmethodID populateExampleSpinner = env->GetMethodID(m_androidExampleControllerViewClass, "PopulateExampleSpinner", "(J[Ljava/lang/String;)V");

	env->CallVoidMethod(
	    m_androidExampleControllerView,
	    populateExampleSpinner,
	    (jlong)(this),
	    stringArray);

	env->DeleteLocalRef(stringArray);
}

void AndroidExampleControllerView::AddSelectPreviousExampleHandler(IUIActionHandler& handler)
{
	m_previousHandlers.push_back(&handler);
}

void AndroidExampleControllerView::RemoveSelectPreviousExampleHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_previousHandlers, &handler);
}

void AndroidExampleControllerView::SelectPrevious()
{
	InvokeAllHandlers(m_previousHandlers);
}

void AndroidExampleControllerView::AddSelectNextExampleHandler(IUIActionHandler& handler)
{
	m_nextHandlers.push_back(&handler);
}

void AndroidExampleControllerView::RemoveSelectNextExampleHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_nextHandlers, &handler);
}

void AndroidExampleControllerView::SelectNext()
{
	InvokeAllHandlers(m_nextHandlers);
}

void AndroidExampleControllerView::AddExampleSelectedHandler(IUIActionHandler& handler)
{
	m_exampleUpdatedHandlers.push_back(&handler);
}

void AndroidExampleControllerView::RemoveExampleSelectedHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_exampleUpdatedHandlers, &handler);
}

void AndroidExampleControllerView::UpdateSelectedExample()
{
	InvokeAllHandlers(m_exampleUpdatedHandlers);
}

void AndroidExampleControllerView::SetCurrentExampleName(const std::string& name)
{
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	jstring exampleNameJni = env->NewStringUTF(name.c_str());
	jmethodID updateExampleSpinnerEntry = env->GetMethodID(m_androidExampleControllerViewClass, "UpdateExampleSpinnerEntry", "(Ljava/lang/String;)V");

	env->CallVoidMethod(
	    m_androidExampleControllerView,
	    updateExampleSpinnerEntry,
	    exampleNameJni);

	env->DeleteLocalRef(exampleNameJni);

	m_selectedExampleName = name;
	UpdateSelectedExample();
}

std::string AndroidExampleControllerView::GetSelectedExample()
{
	return m_selectedExampleName;
}
}
