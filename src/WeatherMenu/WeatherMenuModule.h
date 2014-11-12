// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IWeatherMenuModule.h"
#include "WeatherMenu.h"
#include "Menu.h"
#include "Helpers.h"
#include "CityThemes.h"
#include "UiToNativeMessageBus.h"
#include "WeatherSelectedMessageHandler.h"

namespace ExampleApp
{
namespace WeatherMenu
{
class WeatherMenuModule : public IWeatherMenuModule
{
public:
	WeatherMenuModule(Eegeo::Helpers::IFileIO& fileio,
	                  Eegeo::Resources::CityThemes::ICityThemesService& themesService,
	                  Eegeo::Resources::CityThemes::ICityThemesUpdater& themesUpdater,
	                  ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

	~WeatherMenuModule();

	Menu::IMenuModel& GetWeatherMenuModel() const
	{
		return *m_pMenuModel;
	}
private:

	Menu::IMenuModel* m_pMenuModel;
	Menu::IMenuOptionsModel* m_pMenuOptionsModel;
	IWeatherController* m_pWeatherController;
	WeatherSelectedMessageHandler* m_pWeatherSelectedMessageHandler;
};
}
}
