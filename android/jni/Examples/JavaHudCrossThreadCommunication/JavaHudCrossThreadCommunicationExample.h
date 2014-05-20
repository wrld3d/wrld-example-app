/*
 * JavaHudCrossThreadCommunicationExample.h
 *
 *  Created on: Dec 10, 2013
 *      Author: kimbleoperations
 */

#ifndef JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLE_H_
#define JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLE_H_

#include "IExample.h"
#include "AndroidNativeState.h"
#include "UiThreadToNativeThreadTaskQueue.h"
#include "CityThemes.h"
#include <string>
#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_examples_ThemeReaderWriterHud_setCurrentTheme(JNIEnv* jenv, jobject obj, jlong nativeAppWindowPtr, jstring name);
    JNIEXPORT void JNICALL Java_com_eegeo_examples_ThemeReaderWriterHud_readCurrentThemeName(JNIEnv* jenv, jobject obj, jlong nativeObjectPtr);
}

namespace Examples
{
    class JavaHudCrossThreadCommunicationExample : public IExample
    {
    	AndroidNativeState& m_nativeState;
		Eegeo::Resources::CityThemes::ICityThemesService& m_themeService;
		Eegeo::Resources::CityThemes::ICityThemeRepository& m_themeRepository;
		Eegeo::Resources::CityThemes::ICityThemesUpdater& m_themeUpdater;

    	UiThreadToNativeThreadTaskQueue m_uiToNativeQueue;

    	jclass m_themeReaderWriterHudClass;
    	jobject m_themeReaderWriterHud;

    public:
    	JavaHudCrossThreadCommunicationExample(
			AndroidNativeState& pNativeState,
			Eegeo::Resources::CityThemes::ICityThemesService& themeService,
			Eegeo::Resources::CityThemes::ICityThemeRepository& themeRepository,
			Eegeo::Resources::CityThemes::ICityThemesUpdater& themeUpdater);

    	void PostWorkToNative(UiThreadToNativeThreadTaskQueue::IBufferedWork* work);

        void SetCurrentThemeByName(const std::string& themeName);
        void PostCurrentThemeNameToHud();

        void Start();
        void Update(float dt);
        void Draw() {}
        void Suspend();
    };
}

#endif /* JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLE_H_ */
