// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinAddedToMenuObserver.h"
#include "MyPinsHelpers.h"
#include "IMenuOptionsModel.h"
#include "MyPinModel.h"
#include "MyPinMenuOption.h"

namespace ExampleApp
{
	namespace MyPins
	{
		MyPinAddedToMenuObserver::MyPinAddedToMenuObserver(Menu::IMenuViewModel& menuViewModel,
														   Menu::IMenuOptionsModel& menuOptionsModel,
														   ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
														   ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
		: m_menuViewModel(menuViewModel)
		, m_menuOptionsModel(menuOptionsModel)
		, m_uiToNativeMessageBus(uiToNativeMessageBus)
		, m_nativeToUiMessageBus(nativeToUiMessageBus)
		, m_handlerBinding(this, &MyPinAddedToMenuObserver::HandleReceivedMyPinAddedToMenuMessage)
		{
			m_nativeToUiMessageBus.Subscribe(m_handlerBinding);
		}

		MyPinAddedToMenuObserver::~MyPinAddedToMenuObserver()
		{
			m_nativeToUiMessageBus.Unsubscribe(m_handlerBinding);
		}

		void MyPinAddedToMenuObserver::HandleReceivedMyPinAddedToMenuMessage(const MyPinAddedToMenuMessage& message)
		{
			MyPinModel* myPinModel = message.GetMyPinModel();

            m_menuOptionsModel.AddItem(ConvertModelDetailToString(myPinModel->Identifier()),
                                       myPinModel->GetTitle(),
                                       "",
                                       "place",
                                       Eegeo_NEW(MyPinMenuOption)(*myPinModel, m_menuViewModel, m_uiToNativeMessageBus));
		}
	}
}
