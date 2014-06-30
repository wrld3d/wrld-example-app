// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <jni.h>
#include "ICityThemesUpdater.h"
#include "ICityThemesService.h"
#include "ICityThemeRepository.h"
#include "CityThemeData.h"
#include "JavaHudCrossThreadCommunicationExample.h"
#include "JavaHudCrossThreadCommunicationProxy.h"

namespace Examples
{
//this is the native companion type to com.eegeo.examples.ThemeReaderWriterHud.java
//
JavaHudCrossThreadCommunicationExample::JavaHudCrossThreadCommunicationExample(
    AndroidNativeState& nativeState,
    Eegeo::Resources::CityThemes::ICityThemesService& themeService,
    Eegeo::Resources::CityThemes::ICityThemeRepository& themeRepository,
    Eegeo::Resources::CityThemes::ICityThemesUpdater& themeUpdater,
    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController
)
	: m_nativeState(nativeState)
	, m_themeService(themeService)
	, m_themeUpdater(themeUpdater)
	, m_themeRepository(themeRepository)
	, m_initialCityTheme(themeService.GetCurrentTheme())
	, m_globeCameraStateRestorer(globeCameraController)
{

}

JavaHudCrossThreadCommunicationExample::~JavaHudCrossThreadCommunicationExample()
{

}

void JavaHudCrossThreadCommunicationExample::Start()
{
	//get an env for the current thread
	//
	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//get the java HudPinController class
	jstring strClassName = env->NewStringUTF("com/eegeo/examples/themereaderwriter/ThemeReaderWriterHud");
	jclass themeReaderWriterHudClass = m_nativeState.LoadClass(env, strClassName);
	env->DeleteLocalRef(strClassName);

	//create a persistent reference to the class
	m_themeReaderWriterHudClass = static_cast<jclass>(env->NewGlobalRef(themeReaderWriterHudClass));

	//get the constructor for the ThemeReaderWriterHud, which takes the activity as a parameter
	jmethodID themeReaderWriterHudClassConstructor = env->GetMethodID(m_themeReaderWriterHudClass, "<init>", "(Lcom/eegeo/MainActivity;)V");

	//construct an instance of the ThemeReaderWriterHud, and create and cache a persistent reference to it.
	//we will make calls on to this instance, and it will add elements to the UI for us from Java.
	//we can later use this cached reference to destroy the UI
	jobject instance = env->NewObject(m_themeReaderWriterHudClass, themeReaderWriterHudClassConstructor, m_nativeState.activity);
	m_themeReaderWriterHud = env->NewGlobalRef(instance);

	//get the showUi method, and call it on the instance we have created - the 'J'
	//argument refers to a long - we will carriage a pointer to this so we can be called
	//back by the java code when a menu item is selected
	jmethodID showVisitMenu = env->GetMethodID(m_themeReaderWriterHudClass, "showUi", "(J)V");

	env->CallVoidMethod(
	    m_themeReaderWriterHud,
	    showVisitMenu,
	    (jlong)(this));
}

void JavaHudCrossThreadCommunicationExample::Suspend()
{
	//get an env for the current thread
	//
	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//get the method to remove the menu, and remove menu
	jmethodID removeUi = env->GetMethodID(m_themeReaderWriterHudClass, "removeUi", "()V");
	env->CallVoidMethod(m_themeReaderWriterHud, removeUi);

	//delete the persistent references to the class and object
	env->DeleteGlobalRef(m_themeReaderWriterHudClass);
	env->DeleteGlobalRef(m_themeReaderWriterHud);

	m_themeService.SetSpecificTheme(m_initialCityTheme);
}

void JavaHudCrossThreadCommunicationExample::SetCurrentThemeByName(const std::string& themeName)
{
	m_themeUpdater.SetEnabled(false);
	const Eegeo::Resources::CityThemes::CityThemeData& themeDataToSelect = m_themeRepository.GetThemeDataByName(themeName);
	m_themeService.SetSpecificTheme(themeDataToSelect);
}

void JavaHudCrossThreadCommunicationExample::PostCurrentThemeNameToHud()
{
	//get an env for the current thread
	//
	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//get current theme name to send to the UI, and create a jstring to pass over the JNI
	//from the char buffer. NewStringUTF should perform a copy, which is GC'd by the JVM.
	std::string currentThemeName = m_themeService.GetCurrentTheme().Name;
	jstring themeNameJni = env->NewStringUTF(currentThemeName.c_str());

	//get the method to setCurrentThemeName which takes a java string and returns void, and call it
	jmethodID setCurrentThemeName = env->GetMethodID(m_themeReaderWriterHudClass, "setCurrentThemeName", "(Ljava/lang/String;)V");
	env->CallVoidMethod(m_themeReaderWriterHud, setCurrentThemeName, themeNameJni);

	env->DeleteLocalRef(themeNameJni);
}
}
