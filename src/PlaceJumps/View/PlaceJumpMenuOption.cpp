// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PlaceJumpMenuOption.h"

namespace ExampleApp
{
	namespace PlaceJumps
	{
		PlaceJumpMenuOption::PlaceJumpMenuOption(PlaceJumpModel jumpModel,
							ExampleApp::Menu::IMenuViewModel& menuViewModel,
							ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
			: m_jumpModel(jumpModel)
			, m_menuViewModel(menuViewModel)
			, m_uiToNativeMessageBus(uiToNativeMessageBus)
		{
		}

		void PlaceJumpMenuOption::Select()
		{
			m_menuViewModel.Close();
			m_uiToNativeMessageBus.Publish(PlaceJumpSelectedMessage(m_jumpModel));
		}
	}
}
