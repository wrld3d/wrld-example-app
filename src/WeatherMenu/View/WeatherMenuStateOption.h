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
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

			void Select();

		private:

			WeatherMenuStateModel m_weatherStateModel;
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
		};
	}
}
