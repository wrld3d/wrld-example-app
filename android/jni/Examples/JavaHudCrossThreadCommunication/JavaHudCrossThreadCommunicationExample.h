// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLE_H_
#define JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLE_H_

#include "IExample.h"
#include "AndroidNativeState.h"
#include "CityThemes.h"
#include "CityThemeData.h"
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
	Eegeo::Resources::CityThemes::CityThemeData m_initialCityTheme;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

	jclass m_themeReaderWriterHudClass;
	jobject m_themeReaderWriterHud;

public:
	JavaHudCrossThreadCommunicationExample(
	    AndroidNativeState& pNativeState,
	    Eegeo::Resources::CityThemes::ICityThemesService& themeService,
	    Eegeo::Resources::CityThemes::ICityThemeRepository& themeRepository,
	    Eegeo::Resources::CityThemes::ICityThemesUpdater& themeUpdater,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);

	~JavaHudCrossThreadCommunicationExample();

	void SetCurrentThemeByName(const std::string& themeName);
	void PostCurrentThemeNameToHud();

	static std::string GetName()
	{
		return "JavaHudCrossThreadCommunicationExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt) {}
	void Draw() {}
	void Suspend();
};
}


#endif /* JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLE_H_ */
