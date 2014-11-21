// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "Menu.h"
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"
#include "MyPinAddedToMenuMessage.h"

namespace ExampleApp
{
	namespace MyPins
	{
		class MyPinAddedToMenuObserver
		{
		public:
			MyPinAddedToMenuObserver(Menu::IMenuViewModel& menuViewModel,
									 Menu::IMenuOptionsModel& menuOptionsModel,
                                     ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                     ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);

			~MyPinAddedToMenuObserver();

		private:
			Menu::IMenuViewModel& m_menuViewModel;
			Menu::IMenuOptionsModel& m_menuOptionsModel;
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
			Eegeo::Helpers::TCallback1<MyPinAddedToMenuObserver, const MyPinAddedToMenuMessage&> m_handlerBinding;

			void HandleReceivedMyPinAddedToMenuMessage(const MyPinAddedToMenuMessage& message);
		};
	}
}
