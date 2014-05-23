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
#include "CityThemes.h"
#include "MessageQueue.h"
#include "IAndroidExampleMessage.h"
#include <string>
#include <jni.h>

namespace Examples
{
    class JavaHudCrossThreadCommunicationExample : public IExample
    {
    	AndroidNativeState& m_nativeState;
		Eegeo::Resources::CityThemes::ICityThemesService& m_themeService;
		Eegeo::Resources::CityThemes::ICityThemeRepository& m_themeRepository;
		Eegeo::Resources::CityThemes::ICityThemesUpdater& m_themeUpdater;

    	Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& m_messageQueue;

    	jclass m_themeReaderWriterHudClass;
    	jobject m_themeReaderWriterHud;

    public:
    	JavaHudCrossThreadCommunicationExample(
			AndroidNativeState& pNativeState,
	    	Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue,
			Eegeo::Resources::CityThemes::ICityThemesService& themeService,
			Eegeo::Resources::CityThemes::ICityThemeRepository& themeRepository,
			Eegeo::Resources::CityThemes::ICityThemesUpdater& themeUpdater);

    	void SendMessage(IAndroidExampleMessage* pMessage);

        void SetCurrentThemeByName(const std::string& themeName);
        void PostCurrentThemeNameToHud();

        void Start();
        void Update(float dt) {}
        void Draw() {}
        void Suspend();
    };
}


#endif /* JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLE_H_ */
