//
//  ControlCityThemeExample.h
//  ExampleApp
//
//  Created by Tim Jenks on 12/11/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef ExampleApp_ControlCityThemeExample_h
#define ExampleApp_ControlCityThemeExample_h

#include "IExample.h"
#include "CityThemes.h"
#include "CityThemeData.h"

namespace Examples
{
class ControlCityThemeExample : public IExample
{
private:
	Eegeo::Resources::CityThemes::ICityThemesService& m_themeService;
	Eegeo::Resources::CityThemes::ICityThemeRepository& m_themeRepository;
	Eegeo::Resources::CityThemes::ICityThemesUpdater& m_themeUpdater;
	Eegeo::EegeoWorld& m_eegeoWorld;
	bool m_themeChanged;
	Eegeo::Resources::CityThemes::CityThemeData m_initialCityTheme;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

	void ChangeTheme();
	void FindThemeByPointInPolygon();
public:
	ControlCityThemeExample(Eegeo::Resources::CityThemes::ICityThemesService& themeService,
	                        Eegeo::Resources::CityThemes::ICityThemeRepository& themeRepository,
	                        Eegeo::Resources::CityThemes::ICityThemesUpdater& themeUpdater,
	                        Eegeo::EegeoWorld& eegeoWorld,
	                        Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

	static std::string GetName()
	{
		return "ControlCityThemeExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void Update(float dt);
	void Draw() {}
	void Suspend();
};
}


#endif
