/*
 * JavaHudCrossThreadCommunicationExample.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: kimbleoperations
 */

#include <jni.h>
#include "ICityThemesUpdater.h"
#include "ICityThemesService.h"
#include "ICityThemeRepository.h"
#include "CityThemeData.h"
#include "JavaHudCrossThreadCommunicationExample.h"

namespace Examples
{
//this is the native companion type to com.eegeo.examples.ThemeReaderWriterHud.java
//
	JavaHudCrossThreadCommunicationExample::JavaHudCrossThreadCommunicationExample(
		AndroidNativeState& nativeState,
		Eegeo::Resources::CityThemes::ICityThemesService& themeService,
		Eegeo::Resources::CityThemes::ICityThemeRepository& themeRepository,
		Eegeo::Resources::CityThemes::ICityThemesUpdater& themeUpdater
	)
	: m_nativeState(nativeState)
	, m_themeService(themeService)
	, m_themeUpdater(themeUpdater)
	, m_themeRepository(themeRepository)
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
		jstring strClassName = env->NewStringUTF("com/eegeo/examples/ThemeReaderWriterHud");
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

		jlong pointerToThis = (jlong)(this);
		env->CallVoidMethod(m_themeReaderWriterHud, showVisitMenu, pointerToThis);
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
	}

    void JavaHudCrossThreadCommunicationExample::Update(float dt)
    {
    	m_uiToNativeQueue.TryExectuteBufferedWork();
    }

    void JavaHudCrossThreadCommunicationExample::PostWorkToNative(UiThreadToNativeThreadTaskQueue::IBufferedWork* pWork)
    {
    	m_uiToNativeQueue.PostWork(pWork);
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

class SetCurrentThemeWorkItem : public UiThreadToNativeThreadTaskQueue::IBufferedWork
{
	Examples::JavaHudCrossThreadCommunicationExample* m_pExample;
	std::string m_name;

public:
	SetCurrentThemeWorkItem(Examples::JavaHudCrossThreadCommunicationExample* pExample, std::string name)
	: m_pExample(pExample)
	, m_name(name) {
	}

	void DoWork() {
		//now we are executing on the main thread, so can safely read and write native structures
		m_pExample->SetCurrentThemeByName(m_name);

		// A little untidy, but we know it was dynamically allocated below in Java handler...
		delete this;
	}
};

class GetCurrentThemeWorkItem : public UiThreadToNativeThreadTaskQueue::IBufferedWork
{
	Examples::JavaHudCrossThreadCommunicationExample* m_pExample;

public:
	GetCurrentThemeWorkItem(Examples::JavaHudCrossThreadCommunicationExample* pExample)
	: m_pExample(pExample) {
	}

	void DoWork() {
		//now we are executing on the main thread, so can safely read and write native structures
		m_pExample->PostCurrentThemeNameToHud();

		// A little untidy, but we know it was dynamically allocated below in Java handler...
		delete this;
	}
};

JNIEXPORT void JNICALL Java_com_eegeo_examples_ThemeReaderWriterHud_setCurrentTheme(JNIEnv* jenv, jobject obj, jlong nativeObjectPtr, jstring name)
{
	//extract the string from java via the JNI
	const char* chars = jenv->GetStringUTFChars(name, 0);
	std::string nameString = chars;
	jenv->ReleaseStringUTFChars(name, chars);

	//create a an item to set the theme and post it to our thread safe queue for deferred execution on native main thread
	Examples::JavaHudCrossThreadCommunicationExample* example = (Examples::JavaHudCrossThreadCommunicationExample*)(nativeObjectPtr);
	example->PostWorkToNative(new SetCurrentThemeWorkItem(example, nameString));
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_ThemeReaderWriterHud_readCurrentThemeName(JNIEnv* jenv, jobject obj, jlong nativeObjectPtr)
{
	//create a an item to read the theme and post it to our thread safe queue for deferred execution on native main thread
	Examples::JavaHudCrossThreadCommunicationExample* example = (Examples::JavaHudCrossThreadCommunicationExample*)(nativeObjectPtr);
	example->PostWorkToNative(new GetCurrentThemeWorkItem(example));
}
