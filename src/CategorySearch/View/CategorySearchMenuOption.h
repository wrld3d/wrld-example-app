// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "CategorySearchModel.h"
#include "Search.h"
#include "Menu.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
	namespace CategorySearch
	{
		class CategorySearchMenuOption : public Menu::IMenuOption
		{
			CategorySearchModel m_model;
			ExampleApp::Menu::IMenuViewModel& m_menuViewModel;
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;

		public:
			CategorySearchMenuOption(CategorySearchModel model,
			                         ExampleApp::Menu::IMenuViewModel& menuViewModel,
			                         ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

			~CategorySearchMenuOption();

			void Select();
		};
	}
}
