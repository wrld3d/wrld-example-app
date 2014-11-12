// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "WeatherMenuStateModel.h"
#include "UiToNativeMessageBus.h"
#include "WeatherSelectedMessage.h"

namespace ExampleApp
{
namespace WeatherMenu
{
class WeatherMenuStateOption : public Menu::IMenuOption
{
public:
	WeatherMenuStateOption(
	    WeatherMenuStateModel& weatherStateModel,
	    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
		: m_weatherStateModel(weatherStateModel)
		, m_uiToNativeMessageBus(uiToNativeMessageBus)
	{
	}

	void Select()
	{
		m_uiToNativeMessageBus.Publish(WeatherSelectedMessage(m_weatherStateModel));
	}

private:

	WeatherMenuStateModel m_weatherStateModel;
	ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
};
}
}
